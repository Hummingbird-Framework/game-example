#ifndef HB_VECTOR_3D_H
#define HB_VECTOR_3D_H
#include <cmath>
#include "Vector2d.h"

#define PI 3.14159265

namespace hb
{
	class Vector3d
	{
	public:
		double x, y, z;
		Vector3d(): x(0), y(0), z(0){};
		Vector3d(double x, double y, double z): x(x), y(y), z(z){};
		Vector3d(const Vector3d& v): x(v.x), y(v.y), z(v.z){};
		Vector3d(const Vector2d& v): x(v.x), y(v.y), z(0){};
		Vector3d(const Vector2d& v, double z): x(v.x), y(v.y), z(z){};
		Vector3d(const std::string& str): x(0), y(0), z(0)
		{
			std::regex re ("\\(\\s*([0-9]+(?:\\.[0-9]+)?)\\s*,\\s*([0-9]+(?:\\.[0-9]+)?)\\s*,\\s*([0-9]+(?:\\.[0-9]+)?)\\s*\\)");
			std::smatch sm;
			std::regex_match (str, sm, re);
			if (not sm.empty())
			{
				x = strtod(sm.str(1).c_str(), NULL);
				y = strtod(sm.str(2).c_str(), NULL);
				z = strtod(sm.str(3).c_str(), NULL);
			}
		}

		Vector3d rotatedXZ(double degrees) const;
		Vector3d rotatedXY(double degrees) const;
		Vector3d rotatedYZ(double degrees) const;

		Vector3d multiply(const Vector3d& v) const
		{return Vector3d(x * v.x, y * v.y, z * v.z);}

		double module() const
		{return sqrt(pow(x, 2) + pow(y, 2));}

		Vector3d normalized() const
		{
			Vector3d v = *this;
			double module = this->module();
			if (module != 0.)
			{
				v.x /= module;
				v.y /= module;
				v.z /= module;
			}
			return v;
		}

		Vector2d xy()
		{return Vector2d(x, y);}
	};
	
}

hb::Vector3d operator -(const hb::Vector3d& right);
hb::Vector3d& operator +=(hb::Vector3d& left, const hb::Vector3d& right);
hb::Vector3d& operator -=(hb::Vector3d& left, const hb::Vector3d& right);
hb::Vector3d operator +(const hb::Vector3d& left, const hb::Vector3d& right);
hb::Vector3d operator -(const hb::Vector3d& left, const hb::Vector3d& right);
hb::Vector3d operator *(const hb::Vector3d& left, double right);
hb::Vector3d operator *(double left, const hb::Vector3d& right);
hb::Vector3d& operator *=(hb::Vector3d& left, double right);
hb::Vector3d operator /(const hb::Vector3d& left, double right);
hb::Vector3d& operator /=(hb::Vector3d& left, double right);
bool operator ==(const hb::Vector3d& left, const hb::Vector3d& right);
bool operator !=(const hb::Vector3d& left, const hb::Vector3d& right);
#endif
