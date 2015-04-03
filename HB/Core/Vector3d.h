#ifndef HB_VECTOR_3D_H
#define HB_VECTOR_3D_H
#include <cmath>
#include "Vector2d.h"
#include "Math.h"

namespace hb
{
	/*!
	  \class Vector3d
	  \ingroup core
	  \brief A 3D vector
	*/
	class Vector3d
	{
	public:
		double x; //!< x component of the vector.
		double y; //!< y component of the vector.
		double z; //!< z component of the vector.
		/*!
		  \brief Default constructor.

		  All values to 0.
		*/
		Vector3d(): x(0), y(0), z(0){};
		/*!
		  \brief Contruct a Vector2d from two doubles.
		  \param x Value of x component.
		  \param y Value of y component.
		  \param z Value of z component.
		*/
		Vector3d(double x, double y, double z): x(x), y(y), z(z){};
		/*!
		  \brief Copy constructor.
		  \param v Original instance.
		*/
		Vector3d(const Vector3d& v): x(v.x), y(v.y), z(v.z){};
		/*!
		  \brief Implicit cast from Vector2d (z = 0).
		  \param v Original Vector2d.
		*/
		Vector3d(const Vector2d& v): x(v.x), y(v.y), z(0){};
		/*!
		  \brief Implicit cast from Vector2d setting the z component.
		  \param v Origina Vector2d.
		  \param z New z value.
		*/
		Vector3d(const Vector2d& v, double z): x(v.x), y(v.y), z(z){};

		/*!
		  \brief Get the vector rotated over the XZ plane.
		  \param degrees Number of degrees to be rotated.
		  \return A new instance of Vector3d with the vector rotated.
		*/
		Vector3d rotatedXZ(double degrees) const;
		/*!
		  \brief Get the vector rotated over the XY plane.
		  \param degrees Number of degrees to be rotated.
		  \return A new instance of Vector3d with the vector rotated.
		*/
		Vector3d rotatedXY(double degrees) const;
		/*!
		  \brief Get the vector rotated over the YZ plane.
		  \param degrees Number of degrees to be rotated.
		  \return A new instance of Vector3d with the vector rotated.
		*/
		Vector3d rotatedYZ(double degrees) const;

		/*!
		  \brief Multiply two vectors component by component.
		  \return The resulting Vector3d.
		*/
		Vector3d multiply(const Vector3d& v) const
		{return Vector3d(x * v.x, y * v.y, z * v.z);}

		/*!
		  \brief Get the module of the Vector3d.
		  \return Module of the Vector3d.
		*/
		double module() const
		{return sqrt(pow(x, 2) + pow(y, 2));}

		/*!
		  \brief Get the vector normalied.
		  \return A new instance of Vector3d being the normalized version of the original.
		*/
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

		/*!
		  \brief Get the Vector2d formed by the x and y components of the Vector3d.
		  \return A Vector2d formed by the x and y components of the Vector3d.
		*/
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
