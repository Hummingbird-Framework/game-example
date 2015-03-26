#ifndef HB_VECTOR_2D_H
#define HB_VECTOR_2D_H
#include <cmath>
#include <string>
#include <cstdlib>
#include <regex>

namespace hb
{
	class Vector2d
	{
	public:
		double x, y;
		Vector2d(): x(0), y(0){};
		Vector2d(double x, double y): x(x), y(y){};
		Vector2d(const Vector2d& v): x(v.x), y(v.y){};
		Vector2d(const std::string& str): x(0), y(0)
		{
			std::regex re ("\\(\\s*([0-9]+(?:\\.[0-9]+)?)\\s*,\\s*([0-9]+(?:\\.[0-9]+)?)\\s*\\)");
			std::smatch sm;
			std::regex_match (str, sm, re);
			if (not sm.empty())
			{
				x = strtod(sm.str(1).c_str(), NULL);
				y = strtod(sm.str(2).c_str(), NULL);
			}
		}

		double module() const
		{return sqrt(pow(x, 2) + pow(y, 2));}

		Vector2d normalized() const
		{
			Vector2d v = *this;
			double module = this->module();
			if (module != 0.)
			{
				v.x /= module;
				v.y /= module;
			}
			return v;
		}
	};
	
}

hb::Vector2d operator -(const hb::Vector2d& right);
hb::Vector2d& operator +=(hb::Vector2d& left, const hb::Vector2d& right);
hb::Vector2d& operator -=(hb::Vector2d& left, const hb::Vector2d& right);
hb::Vector2d operator +(const hb::Vector2d& left, const hb::Vector2d& right);
hb::Vector2d operator -(const hb::Vector2d& left, const hb::Vector2d& right);
hb::Vector2d operator *(const hb::Vector2d& left, double right);
hb::Vector2d operator *(double left, const hb::Vector2d& right);
hb::Vector2d& operator *=(hb::Vector2d& left, double right);
hb::Vector2d operator /(const hb::Vector2d& left, double right);
hb::Vector2d& operator /=(hb::Vector2d& left, double right);
bool operator ==(const hb::Vector2d& left, const hb::Vector2d& right);
bool operator !=(const hb::Vector2d& left, const hb::Vector2d& right);
#endif

/**
 * \class hb::Vector2d
 * \ingroup core
 *
 * A 2d vector of doubles
 */
