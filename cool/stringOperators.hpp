#ifndef COOL_STRINGOPERATORS_HPP
#define COOL_STRINGOPERATORS_HPP

#include <string>


#if _HAS_CXX20 and 0

template<class T>
concept Has_to_string = requires(T a)
{
    std::to_string(a);
};

template<Has_to_string T>
std::string operator+(const std::string& s, T num) 
{
    return s + std::to_string(num);
}

template<Has_to_string T>
std::string operator+= (std::string& s, T num)
{
    s = s + num;
    return s;
}

#else

std::string operator+(const std::string& s, int num)
{
    return s + std::to_string(num);
}

std::string operator+(const std::string& s, unsigned long long num)
{
    return s + std::to_string(num);
}

std::string operator+(const std::string& s, float num)
{
    return s + std::to_string(num);
}

std::string operator+(const std::string& s, double num)
{
    return s + std::to_string(num);
}

std::string operator+(const std::string& s, long double num)
{
    return s + std::to_string(num);
}
//====

std::string operator+= (std::string& s, int num)
{
    s = s + num;
    return s;
}

std::string operator+= (std::string& s, unsigned long long num)
{
    s = s + num;
    return s;
}

std::string operator+= (std::string& s, float num)
{
    s = s + num;
    return s;
}

std::string operator+= (std::string& s, double num)
{
    s = s + num;
    return s;
}


std::string operator+= (std::string& s, long double num)
{
    s = s + num;
    return s;
}

#endif



std::string operator*(const std::string& s_, int num) {
    auto s = s_;
    for (int i = 1; i < num; i++)
    {
        s += s_;
    }
    return s;
}

std::string operator*= (std::string& s, int num)
{
    s = s * num;
    return s;
}

namespace std
{
    string to_string(const string s)
    {
        return s;
    }
}

#endif