#ifndef COOL_BOOSTFORMATLITERAL_HPP
#define COOL_BOOSTFORMATLITERAL_HPP

#include <boost/format.hpp>

namespace cool
{
	namespace boost
	{
		namespace literals
		{
			::boost::format operator ""_f(const char* cstr, size_t size)
			{
				return ::boost::format(cstr);
			}
		}
	}
}

#endif

