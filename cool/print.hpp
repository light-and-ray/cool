#ifndef COOL_PRINT_HPP
#define COOL_PRINT_HPP

#include <string>
#include <iostream>
#include <iomanip>

namespace
{
	std::ostream* out = &std::cout;
}

namespace cool
{
	inline void setCyrillic()
	{
		setlocale(LC_ALL, "Russian");
	}

	void setPrintOut(std::ostream& os)
	{
		::out = &os;
	}

	std::ostream* getPrintOutPtr()
	{
		return ::out;
	}
	

	inline void print() 
	{ 
		*::out << ' ';
	}

	template <typename Arg>
	inline void print(const Arg& arg)
	{
		*::out <<  std::fixed << std::setprecision(4) << arg << ' ';
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
		*::out << '\n';
	}
	template <typename Arg>
	inline void println(const Arg& arg)
	{
		*::out << std::fixed << std::setprecision(4) << arg << '\n';
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
		*::out << std::fixed << std::setprecision(4) << arg;
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
