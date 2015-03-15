#ifndef HB_TRANSFORM_H
#define HB_TRANSFORM_H
#include "Vector3d.h"

namespace hb
{
	class Transform
	{
	public:
		Transform();
		Transform(const Vector3d& init_pos);
		~Transform();
		const Vector3d& getPosition() const;
		void setPosition(const Vector3d& p);
		void setPosition(double p_x, double p_y, double p_z);
		const Vector3d& getRotation() const;
		void setRotation(const Vector3d& rotation);
		void setRotation(double rotation_x, double rotation_y, double rotation_z);
		const Vector3d& getScale() const;
		void setScale(const Vector3d& scale);
		void setScale(double scale_x, double scale_y, double scale_z);

	private:
		Vector3d m_position;
		Vector3d m_scale;
		Vector3d m_rotation_angle;
	};
}
#endif