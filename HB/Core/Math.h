#ifndef HB_MATH_H
#define HB_MATH_H

#define PI 3.14159265

namespace hb
{

	inline double radToDeg(double rad)
	{
		return rad/PI * 180.;
	}


	inline double degToRad(double deg)
	{
		return PI * deg/180.;
	}
}

#endif