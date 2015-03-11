#ifndef HB_CAMERA_H
#define HB_CAMERA_H
#include <utility>
#include "../Base/Transform.h"

namespace hb
{
	class Camera
	{
	public:
		Camera();
		~Camera();
		void setPosition(const Vector3d& pos);
		void setAxisX(const Vector3d& x);
		void setAxisY(const Vector3d& y);
		void setAxisZ(const Vector3d& z);
		void setZNear(double zn);
		void setZFar(double zf);

		const Vector3d& getPosition() const;
		const Vector3d& getAxisX() const;
		const Vector3d& getAxisY() const;
		const Vector3d& getAxisZ() const;
		double getZNear() const;
		double getZFar() const;

	private:
		Vector3d m_position, m_x, m_y, m_z;
		double m_zn, m_zf;
	};
}
#endif