#ifndef HB_VECTOR_2D_H
#define HB_VECTOR_2D_H
#include <cmath>
#include <string>
#include <cstdlib>

namespace hb
{
	/*!
	  \class Vector2d
	  \ingroup core
	  \brief A 2D vector.
	*/
	class Vector2d
	{
	public:
		double x; //!< x component of the vector.
		double y; //!< y component of the vector.
		/*!
		  \brief Default constructor.

		  All values to 0.
		*/
		Vector2d(): x(0), y(0){};
		/*!
		  \brief Contruct a Vector2d from two doubles.
		  \param x Value of x component.
		  \param y Value of y component.
		*/
		Vector2d(double x, double y): x(x), y(y){};
		/*!
		  \brief Copy constructor.
		  \param v Original instance.
		*/
		Vector2d(const Vector2d& v): x(v.x), y(v.y){};

		/*!
		  \brief Get the module of the Vector2d.
		  \return Module of the Vector2d.
		*/
		double module() const
		{return sqrt(pow(x, 2) + pow(y, 2));}

		/*!
		  \brief Get the vector normalied.
		  \return A new instance of Vector2d being the normalized version of the original.
		*/
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
