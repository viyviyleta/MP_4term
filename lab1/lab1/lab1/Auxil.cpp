#include "stdafx.h"

namespace auxil
{
	//старт генератора чисел
	void start()
	{
		srand((unsigned)time(NULL));
	};

	//получить случайное число
	double dget(double rmin, double rmax)
	{
		return ((double)rand() / (double)RAND_MAX) * (rmax - rmin) + rmin;
	};

	//получить случайное число
	int iget(int rmin, int rmax)
	{
		return (int)dget((double)rmin, (double)rmax);
	};
}
