#include "Vector3d.h"
using namespace hb;

Vector3d Vector3d::rotatedXZ(double degrees) const
{
	degrees *= (PI/180.0);
	Vector3d tmp = Vector3d(*this);
	tmp.z = (double) (tmp.z * cos(degrees) - tmp.x * sin(degrees));
	tmp.x = (double) (tmp.z * sin(degrees) + tmp.x * cos(degrees));
	return tmp;
}


Vector3d Vector3d::rotatedXY(double degrees) const
{
	degrees *= (PI/180.0);
	Vector3d tmp = Vector3d(*this);
	tmp.y = (double) (tmp.y * cos(degrees) - tmp.x * sin(degrees));
	tmp.x = (double) (tmp.y * sin(degrees) + tmp.x * cos(degrees));
	return tmp;
}


Vector3d Vector3d::rotatedYZ(double degrees) const
{
	degrees *= (PI/180.0);
	Vector3d tmp = Vector3d(*this);
	tmp.z = (double) (tmp.z * cos(degrees) - tmp.y * sin(degrees));
	tmp.y = (double) (tmp.z * sin(degrees) + tmp.y * cos(degrees));
	return tmp;
}


Vector3d operator -(const Vector3d& right)
{
	return Vector3d(-right.x, -right.y, -right.z);
}


Vector3d& operator +=(Vector3d& left, const Vector3d& right)
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	return left;
}


Vector3d& operator -=(Vector3d& left, const Vector3d& right)
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	return left;
}


Vector3d operator +(const Vector3d& left, const Vector3d& right)
{
	return Vector3d(left.x + right.x, left.y + right.y, left.z + right.z);
}


Vector3d operator -(const Vector3d& left, const Vector3d& right)
{
	return Vector3d(left.x - right.x, left.y - right.y, left.z - right.z);
}


Vector3d operator *(const Vector3d& left, double right)
{
	return Vector3d(left.x * right, left.y * right, left.z * right);
}


Vector3d operator *(double left, const Vector3d& right)
{
	return Vector3d(left * right.x, left * right.y, left * right.z);
}


Vector3d& operator *=(Vector3d& left, double right)
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	return left;
}


Vector3d operator /(const Vector3d& left, double right)
{
	Vector3d ret(left);
	ret.x /= right;
	ret.y /= right;
	ret.z /= right;
	return ret;
}


Vector3d& operator /=(Vector3d& left, double right)
{
	left.x /= right;
	left.y /= right;
	left.z /= right;
	return left;
}


bool operator ==(const Vector3d& left, const Vector3d& right)
{
	return (left.x == right.x and left.y == right.y and left.z == right.z);
}


bool operator !=(const Vector3d& left, const Vector3d& right)
{
	return not (left.x == right.x and left.y == right.y and left.z == right.z);
}
