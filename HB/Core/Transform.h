#ifndef HB_TRANSFORM_H
#define HB_TRANSFORM_H
#include "Vector3d.h"

namespace hb
{
	/*!
	  \class Transform
	  \ingroup core
	  \brief Object with a position, rotation and scale in a 3D space.
	*/
	class Transform
	{
	public:
		/*!
		  \brief Default constructor.

		  All values to 0.
		*/
		Transform();
		/*!
		  \brief Constructor with initial position.
		*/
		Transform(const Vector3d& init_pos);
		/*!
		  \brief Class destructor.
		*/
		~Transform();
		/*!
		  \brief Get Transform position.
		  \return Transform position.
		*/
		const Vector3d& getPosition() const;
		/*!
		  \brief Set position from a Vector3d.
		  \param p New position
		*/
		void setPosition(const Vector3d& p);
		/*!
		  \brief Set position from doubles.
		  \param p_x New x position.
		  \param p_y New y position.
		  \param p_z New z position.
		*/
		void setPosition(double p_x, double p_y, double p_z);
		/*!
		  \brief Get Transform rotation.
		  \return Transform rotation.
		*/
		const Vector3d& getRotation() const;
		/*!
		  \brief Set rotation from a Vector3d.
		  \param rotation New rotation
		*/
		void setRotation(const Vector3d& rotation);
		/*!
		  \brief Set rotation from doubles.
		  \param rotation_x New rotation around the X axis.
		  \param rotation_y New rotation around the Y axis.
		  \param rotation_z New rotation around the Z axis.
		*/
		void setRotation(double rotation_x, double rotation_y, double rotation_z);
		/*!
		  \brief Get Transform scale.
		  \return Transform scale.
		*/
		const Vector3d& getScale() const;
		/*!
		  \brief Set scale from a Vector3d.
		  \param scale New scale
		*/
		void setScale(const Vector3d& scale);
		/*!
		  \brief Set position from doubles.
		  \param scale_x New scale over the X axis.
		  \param scale_y New scale over the Y axis.
		  \param scale_z New scale over the Z axis.
		*/
		void setScale(double scale_x, double scale_y, double scale_z);

	private:
		Vector3d m_position;
		Vector3d m_scale;
		Vector3d m_rotation_angle;
	};
}
#endif