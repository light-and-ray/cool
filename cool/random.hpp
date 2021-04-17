#ifndef COOL_RANDOM_HPP
#define COOL_RANDOM_HPP

#include <ctime>
#include <cmath>

namespace cool
{
	double random(double rmin, double rmax, int c = 4)
	{
		int x = rand();
		double y = x * (rmax - rmin + 1) / RAND_MAX + rmin;
		return round(y * pow(10, c)) / pow(10, c);
	}

	inline double random(double rmax, int c = 4)
	{
		return random(0, rmax, c);
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