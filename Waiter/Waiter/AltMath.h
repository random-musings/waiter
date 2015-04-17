#pragma once

#include <math.h>
class AltMath
{
public:
	AltMath();
	~AltMath();

	static  double sqrt(double x) {
			if (x <= 0)
				return 0;       // if negative number throw an exception?
			int exp = 0;
			x = frexp(x, &exp); // extract binary exponent from x
			if (exp & 1) {      // we want exponent to be even
				exp--;
				x *= 2;
			}
			double y = (1 + x) / 2; // first approximation
			double z = 0;
			while (y != z) {    // yes, we CAN compare doubles here!
				z = y;
				y = (y + x / y) / 2;
			}
			return ldexp(y, exp / 2); // multiply answer by 2^(exp/2)
		}
};

