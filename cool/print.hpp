#ifndef COOL_PRINT_HPP
#define COOL_PRINT_HPP

#include <string>
#include <iostream>
#include <iomanip>

namespace cool
{
	inline void setCyrillic()
	{
		setlocale(LC_ALL, "Russian");
	}

	inline void print() 
	{ 
		std::cout << ' ';
	}

	template <typename Arg>
	inline void print(const Arg& arg)
	{
		std::cout << std::setprecision(4) << std::fixed << arg << ' ';
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
		std::cout << std::setprecision(4) << std::fixed << arg << '\n';
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
		std::cout << std::setprecision(4) << std::fixed << arg;
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