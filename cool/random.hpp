#ifndef COOL_RANDOM_HPP
#define COOL_RANDOM_HPP

#include <ctime>
#include <cmath>

namespace cool
{
	void _init()
	{
		static bool initialized = false;
		if (!initialized){
			srand(time(NULL));
			initialized = true;
		}
	}

	//from rmin to rmin inclusive
	double random(double rmin, double rmax, int precision = 4)
	{
		_init();
		int x = rand();
		double y = x * (rmax - rmin + 1) / RAND_MAX + rmin;
		return round(y * pow(10, precision)) / pow(10, precision);
	}

	//from 0 to rmin inclusive
	inline double random(double rmax, int precision = 4)
	{
		return random(0, rmax, precision);
	}

	//from rmin to rmin inclusive
	int random(int rmin, int rmax)
	{
		_init();
		int x = rand();
		int y = ((long)x * (rmax - rmin + 1)) / RAND_MAX + rmin;
		return y;
	}

	//from 0 to rmin inclusive
	inline int random(int rmax)
	{
		return random(0, rmax);
	}
}

#endif
