#include "Vector3d.h"
using namespace hb;

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
	Vector3d ret;
	ret.x = left.x + right.x;
	ret.y = left.y + right.y;
	ret.z = left.z + right.z;
	return ret;
}


Vector3d operator -(const Vector3d& left, const Vector3d& right)
{
	Vector3d ret;
	ret.x = left.x - right.x;
	ret.y = left.y - right.y;
	ret.z = left.z - right.z;
	return ret;
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