#ifndef COOL_RANDOM_HPP
#define COOL_RANDOM_HPP

#include <ctime>
#include <cmath>

namespace cool
{
	double random(double rmin, double rmax, int precision = 4)
	{
		int x = rand();
		double y = x * (rmax - rmin + 1) / RAND_MAX + rmin;
		return round(y * pow(10, precision)) / pow(10, precision);
	}

	inline double random(double rmax, int precision = 4)
	{
		return random(0, rmax, precision);
	}

	int random(int rmin, int rmax)
	{
		int x = rand();
		int y = double((long)x * (rmax - rmin + 1)) / RAND_MAX + rmin;
		return y;
	}

	inline int random(int rmax)
	{
		return random(0, rmax);
	}
}

#endif