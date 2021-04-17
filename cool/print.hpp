#ifndef COOL_PRINT_HPP
#define COOL_PRINT_HPP

#include <string>
#include <iostream>

namespace cool
{

	void print() { }

	template <typename Arg>
	inline void print(const Arg& arg)
	{
		std::cout << arg << ' ';
	}

	template <typename Arg, typename... Args>
	void print(const Arg& arg, const Args&... args)
	{
		print(arg);
		print(args...);
	}
	////

	inline void println()
	{
		std::cout << '\n';
	}
	template <typename Arg>
	inline void println(const Arg& arg)
	{
		std::cout << arg << '\n';
	}

	template <typename... Args>
	void println(const Args&... args)
	{
		print(args...);
		println();
	}
	///
	void print0() { }

	template <typename Arg>
	inline void print0(const Arg& arg)
	{
		std::cout << arg;
	}

	template <typename Arg, typename... Args>
	void print0(const Arg& arg, const Args&... args)
	{
		print0(arg);
		print0(args...);
	}

#define COOL_INFO(x) (std::string(#x) + " = " + std::to_string(x))
}


#endif