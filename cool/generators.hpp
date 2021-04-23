//why visual studio extends __cplusplus like 199711
#if (__cplusplus > 201703L) or 1

#ifndef COOL_GENERATORS_HPP
#define COOL_GENERATORS_HPP
/*

    C++20 coroutine based generator by Serikov
    https://gist.github.com/Serikov/b28115e3b13a7c0ec45ab76468ddb0bd#file-main-cpp-L53

    Warring, this cool library is non-licensed and only for fun

*/


#include <coroutine>
#include <stdexcept>
#include <variant>
#include <utility>

namespace cool
{
    namespace detail {
        // simple type erasure for iterators

        template<typename T>
        struct generic_iterable
        {
            virtual ~generic_iterable() = default;

            virtual T& operator*() = 0;
            virtual generic_iterable<T>& operator++() = 0;
            virtual bool empty() const = 0;

            bool await_ready() const noexcept
            {
                return empty();
            }

            template<typename U>
            void await_suspend(std::coroutine_handle<U> h) noexcept
            {
                h.promise().store_iterator(this);
            }

            void await_resume() const noexcept {}
        };

        template<typename T, typename StartIterator, typename EndIterator>
        struct iterator_iterable : public generic_iterable<T>
        {
            iterator_iterable(StartIterator start, EndIterator end) : start(start), end(end) {}

            T& operator*() override
            {
                return *start;
            }

            iterator_iterable<T, StartIterator, EndIterator>& operator++() override
            {
                ++start;
                return *this;
            }

            bool empty() const override
            {
                return start == end;
            }

            StartIterator start;
            EndIterator end;
        };

    } // namespace detail

    template<typename T>
    struct generator
    {
        using value_type = T;

        struct promise_type
        {
            // 0: prestart, 1: value, 2: range, 3: done
            std::variant<std::monostate, T*, detail::generic_iterable<T>*, std::monostate> state;

            promise_type& get_return_object() noexcept
            {
                return *this;
            }

            std::suspend_always initial_suspend() const noexcept
            {
                return {};
            }

            std::suspend_always final_suspend() const noexcept
            {
                return {};
            }

            std::suspend_always yield_value(T& value) noexcept
            {
                state.template emplace<1>(std::addressof(value));
                return {};
            }

            std::suspend_always yield_value(T&& value) noexcept
            {
                state.template emplace<1>(std::addressof(value));
                return {};
            }

            void return_void() noexcept
            {
                state.template emplace<3>();
            }

            template<typename Range>
            auto await_transform(Range&& range) const noexcept
            {
                using std::begin;
                using std::end;
                auto s = begin(range);
                auto e = end(range);

                // TODO: properly constraint
                static_assert(std::is_same_v<decltype(*s), T&>);
                detail::iterator_iterable<T, decltype(s), decltype(e)> iterator{ s, e };
                return iterator;
            }

            void unhandled_exception()
            {
                state.template emplace<3>();
                auto ex = std::current_exception();
                std::rethrow_exception(ex);
                //// MSVC bug? should be possible to rethrow with "throw;"
                //// rethrow exception immediately
                // throw;
            }

            void store_iterator(detail::generic_iterable<T>* iterator) noexcept
            {
                state.template emplace<2>(iterator);
            }

            T& value()
            {
                switch (state.index()) {
                case 1:
                    return *std::get<1>(state);
                case 2:
                    return **std::get<2>(state);
                case 0:
                    next();
                    return value();
                default:
                case 3:
                    throw std::logic_error("Generator already completed!");
                }
            }

            const T& value() const
            {
                switch (state.index()) {
                case 1:
                    return *std::get<1>(state);
                case 2:
                    return **std::get<2>(state);
                case 0:
                    next();
                    return value();
                default:
                case 3:
                    throw std::logic_error("Generator already completed!");
                }
            }

            void next()
            {
                auto handle = std::coroutine_handle<promise_type>::from_promise(*this);
                switch (state.index()) {
                case 0:
                case 1:
                    handle.resume();
                    break;
                case 2: {
                    auto& iterator = *std::get<2>(state);
                    ++iterator;
                    if (iterator.empty()) {
                        state.template emplace<0>();
                        handle.resume();
                    }
                    break;
                }
                default:
                case 3:
                    throw std::logic_error("Generator already completed!");
                }
            }
        };

        using handle_type = std::coroutine_handle<promise_type>;

        struct iterator
        {
            using iterator_category = std::input_iterator_tag;
            using value_type = T;
            using difference_type = ptrdiff_t;
            using pointer = T*;
            using reference = T&;

            handle_type coro_handle;

            iterator() : coro_handle(nullptr) {}

            iterator(handle_type coro_handle) : coro_handle(coro_handle) {}

            iterator& operator++()
            {
                try {
                    coro_handle.promise().next();
                }
                catch (...) {
                    coro_handle = nullptr;
                    throw;
                }
                if (coro_handle.done())
                    coro_handle = nullptr;
                return *this;
            }

            iterator operator++(int) = delete;

            bool operator==(iterator const& other) const
            {
                return coro_handle == other.coro_handle;
            }

            bool operator!=(iterator const& other) const
            {
                return !(*this == other);
            }

            const T& operator*() const
            {
                return coro_handle.promise().value();
            }

            const T* operator->() const
            {
                return std::addressof(operator*());
            }

            T& operator*()
            {
                return coro_handle.promise().value();
            }

            T* operator->()
            {
                return std::addressof(operator*());
            }
        };

        iterator begin()
        {
            if (coro_handle) {
                if (coro_handle.done())
                    return {};
            }

            return { coro_handle };
        }

        iterator end()
        {
            return {};
        }

        generator(promise_type& promise) : coro_handle(handle_type::from_promise(promise)) {}

        generator() = default;
        generator(generator const&) = delete;
        generator& operator=(generator const&) = delete;

        generator(generator&& other) noexcept : coro_handle(other.coro_handle)
        {
            other.coro_handle = nullptr;
        }

        generator& operator=(generator&& other)
        {
            if (&other != this) {
                coro_handle = other.coro_handle;
                other.coro_handle = nullptr;
            }
            return *this;
        }

        ~generator()
        {
            if (coro_handle) {
                coro_handle.destroy();
            }
        }

    private:
        std::coroutine_handle<promise_type> coro_handle = nullptr;
    };

    namespace authors_generators
    {

        template<typename T>
        generator<int> range(T first, T last)
        {
            while (first != last) {
                co_yield first++;
            }
        }

        template<typename T>
        generator<int> range1(T first, T last)
        {
            while (first != last) {
                throw std::logic_error("BEGIN");

                co_yield first++;
            }
        }

        template<typename T>
        generator<int> range2(T first, T last)
        {
            while (first != last) {
                co_yield first++;

                throw std::logic_error("ITERATOR");
            }
        }

        template<typename T>
        generator<int> range4(T first, T last)
        {
            co_return;
        }

        template<typename T>
        generator<int> range5_ex(T first, T last)
        {
            while (first != last) {
                co_yield first++;
            }
            throw std::logic_error("AFTER LAST YIELD (for example cleanup failure)");
        }

        /////////////////////////
        generator<std::unique_ptr<int>> range_unqptr(int first, int last)
        {
            while (first != last) {
                co_yield std::make_unique<int>(first++);
            }
        }

        generator<std::unique_ptr<int>> gen_refs()
        {
            auto value = std::make_unique<int>(1);
            co_yield value;                    // lvalue&, can be moved from
            co_yield std::make_unique<int>(2); // rvalue&, can be moved from
            const auto cvalue = std::make_unique<int>(3);
            // co_yield cvalue; // compile error
        }

        generator<const std::unique_ptr<int>> gen_refs2()
        {
            auto value = std::make_unique<int>(1);
            co_yield value;                    // lvalue&
            co_yield std::make_unique<int>(2); // rvalue&
            const auto cvalue = std::make_unique<int>(3);
            co_yield cvalue; // no compile error
        }

        /////////////////////////
        // combining generators and ranges
        generator<int> gen_and_then(generator<int> first, generator<int> second)
        {
            co_await first;
            co_yield 999;
            co_await second;
            co_yield -999;
        }

        template<typename Range1, typename Range2>
        generator<int> and_then(Range1 first, Range2 second)
        {
            co_await first;
            co_yield 999;
            co_await second;
            co_yield -999;
        }
    }

//my code is here



    generator<int> range(auto a, auto b, auto step)
    {
        for (int i = a; i < b; i+=step)
        {
            co_yield i;
        }
    }

    generator<int> range(auto a, auto b)
    {
        for (int i = a; i < b; i += 1)
        {
            co_yield i;
        }
    }

    generator<int> range(auto b)
    {
        for (int i = 0; i < b; i += 1)
        {
            co_yield i;
        }
    }
    
    template <
        typename ResultType,
        template<typename> class Container  >
    auto enumerate(Container<ResultType> container) ->
        generator< std::pair<int, ResultType> >
    {
        int i = 0;
        for (auto elem : container)
        {
            co_yield std::pair<int, ResultType>(i, elem);
            i += 1;
        }
    }

    template <
        typename ResultType,
        template<typename, typename> class Container,
        typename Allocator>
    auto enumerate(Container<ResultType, Allocator> container) ->
        generator< std::pair<int, ResultType> >
    {
        int i = 0;
        for (auto elem : container)
        {
            co_yield std::pair<int, ResultType>(i, elem);
            i += 1;
        }
    }

}

#endif

#endif

