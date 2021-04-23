# Cool
small helping library

маленькая библиотека с полезными функциями для C++ и С11

### Использование

1. Добавьте папку репозитория как дополнительный каталог включения. В Visual Studio это `проект -> свойства -> C/C++ -> общее -> дополнительные каталоги включения` В gcc и clang это параметр `-I`
2. Подключите нужный заголовочный файл с помощью `#include <cool/имя.hpp>`, или `#include <cool/all.hpp>` для подключения всех файлов
3. Все функции находятся в пространстве имен `cool`

## Для C++ 

Пример: https://github.com/light-and-ray/cool/blob/master/example.cpp

### Описание заголовочных файлов
##### `#include <cool/print.hpp>`
`print(Args)` - печатает аргументы через пробел. При передачи одного аргумента выводит его и затем пробел
  
`println(Args)` - аналогичен предыдущему, но добавляет переход на новую строку. Без аргументов перводит на новую строку
  
`print0(Args)` - выводит аргументы друг за другом без никаких дополнительных символов

`printFlush()` - делает flush

`setCyrillic()` - включает кириллицу в консоли - `setlocale(LC_ALL, "Russian")`

`getPrintOutPtr()` - возращает указатель на поток, переданный в предыдущей функции

`setPrintOut(std::ostream)` - устанавливает поток вывода всех функций данной библиотеки (по умолчанию `std::cout`)
  
`COOL_INFO(x)` -  преобразует x в строку вида "x = значение x"  

                   например  int x = 3
                             println( COOL_INFO( x + 2 ) )   
                   выводит   x + 2 = 5


##### `#include <cool/random.hpp>`
        random(start, end)
        start, end - типа int. Возращает случайное число от start до end включительно
        
        random(end)
        end - типа int. Возращает случайное целове число от 0 до end включительно
        
        random(start, end, precision = 4)
        start, end - double, precision - int. Возращает случайное число от start до end включительно 
                                        с точностью до precision знаков после точки (По умолчанию 4)
        
        random(end, precision = 4)
        end - double, precision - int. Возращает случайное число от 0 до end включительно с точностью 
                                                      до precision знаков после точки (По умолчанию 4)
        


##### `#include <cool/stringOperators.hpp>`

1. Добавляет `operator+` для строки и чила типа `int`, `unsigned long long`, `float`, `double`, `long double`
В будущем для C++20 будет работать для любого аргумента, для которого существует std::to_string, но пока что 
по непонятной причине перегружанный `operator+` с концептным шаблоном не имеет приоритет над стандартным. Для перегружанных шаблонных функций такой приоритет есть
    
        Например  std::string s = "wowow";
                  print0(s + " " + 10)
        выводит   wowow 10
2. Добавляет `operator*` для строки и числа `n`, повтаряет строку `n` раз (не самым оптимальным способом, просто складывает `n` раз, но для практического использования сойдёт)
    
        Например  std::string s = "wo"
                  println(s*4)
        выводит   wowowowo

3. Так же определены соответствующие операторы += и *=


##### `#include <cool/boostFormatLiteral.hpp>`

`using namespace cool::boost::literals;` определяет литерал `_f` для строк в кавычках. Более простая запись для `boost::format`

      Запись          cout << boost::format("value x = {%s}, f(x) = {%s}") % x % f(x)
      Заменяется на   cout << "value x = {%s}, f(x) = {%s}"_f   % x % f(x)

Необходима должна быть подключена к проекту библиотека `boost`


##### `#include <cool/generators.hpp>   C++20`

`generator<Type>` - обьект-генератор, имеющий интерфейс, аналогичный контейнерам, но при этом это функция, которая по мере выполнения возвращает значения. Аналогичен генераторам в Python, базируется на стандартной библиотеке сопрограмм `<coroutine>` Код генератора взят здесь https://gist.github.com/Serikov/b28115e3b13a7c0ec45ab76468ddb0bd#file-main-cpp-L53 , `range` и `enumerate` написаны мной

Пример генератора:

    generator<int> range(auto a, auto b)
    {
        for (int i = a; i < b; i += 1)
        {
            co_yield i;
        }
    }
 
 Аналогичный generator есть в файле experimental/genetator в стандартной библиотеке visual studio. Скорее всего его добавят в C++23
 
 
`range(a, b, step)` - возвращает генератор чисел от a до b (невключительно) с шагом step

`range(a, b)` - возвращает генератор чисел от a до b (невключительно) с шагом 1

`range(b)` - возвращает генератор чисел от 0 до b (невключительно) с шагом 1


`enumerate(container)` - создает генератор пар `индекс, элемент` 

Пример использования: 

        
    std::vector v = { "a", "b", "6", "g" };       Вывод:    v[0] = a
    for (auto& [i, x] : enumerate(v))                       v[1] = b
    {                                                       v[2] = 6
        cout << "v[%s] = %s\n"_f % i % x;                   v[3] = g
    }
      



##### `#include <cool/loop.hpp>`
Добавляет бесконечный цикл - `#define loop while(true)`
        
        loop
        {
           /*expressions*/
        }
        
> Мне просто очень нравятся бесконечные циклы :> По сути `while` и `do ... while` - это бесконечные циклы, у который происходит проверка 
> `if (cond) break` в начале или в конце блока. Часто бывает что по ходу написания программы нудно добавить пару строчек перед или после проверки.
> Или вообще бывает много сложных и простых условий выхода, которые неудобно помещать рядом со словом `while`.
> 
> Мне в основном удобно использовать `while` в однострочных или малострочных циклах, в большинстве случаев пишу `while(1)`, или данный define


## Для C11 и выше

Пример: https://github.com/light-and-ray/cool/blob/master/c_example.c

##### `#include <cool/с/print.h>`

`cool_print(Ags)` - печатает аргументы (любого типа!) через символ-разделитель `cool_print_sep`. При передачи одного аргумента выводит его и затем `cool_print_sep`. При передачи 0 аргументов происходит краш с непонятным сообщением об ошибке :)

`cool_println(Args)` - аналогичен предыдущему, но добавляет переход на новую строку. Без аргументов работает происходит ошиюка, воспользуйтесь следущей функцией.

`cool_printlnn()` - перводит на новую строку

`cool_print_sep = " "` - установка разделителя

Для редефайна без приставки `cool_` воспользуйтесь `#include <cool/с/using_print.h>`, для отмены воспользуйтесь `#include <cool/с/unusing_print.h>`

Про эту функцию я написал целую статью: https://habr.com/ru/post/553636/

> Я решил поэксперементировать с джейнериками в C11 и создать удобный `print`, заодно оценив их маощность. И это получилось! Я удивился, что в СИ вообще возможно создать нечто похожее! Правда есть ряд проблем:
> 1. Есть проблема при отсутствии аргументов. По какой-то причине `, ##` в макросах не работает так как надо при обнаружении числа параметров `n` для вызова макроса `cool_print_##n`. Возможно стоит найти возможность проверки на наличие аргументов, но я не могу найти как это реализовать и как в макросах в зависимости от условия. Еще в следущем стандарте планируют добавить идеальный для данного случая `__VA_OPT__`, но сейчас его нет (
> 2. Почему-то при подстановки на первое место аргумента `" "` в теле макроса `COOL_ARG_N`
>  
>            cool_print_##n(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11,_12)
>            
>            --------------^------------------------
> он поднимался на верх и подставлялся первым аргументом в основной макрос `print(...)` оО Очень странное поведение
> 3. Visual Studio потчеркивает почти все макросы красным, но программа компилируется и макросы работают исправно. Не знаю как это исправить, может стоит написать в тех. поддержку VS
> 

##### `#include <cool/с/PP_NARG.H>`
`PP_NARG(__VA_ARGS__)` - возвращает число переданных в макрос аргументов. Код взят из интернета
