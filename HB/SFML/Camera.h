#ifndef HB_CAMERA_H
#define HB_CAMERA_H
#include <utility>
#include "../Core/Transform.h"
#include "../Core/Log.h"

namespace hb
{
	/**
	 * \class Camera
	 * \ingroup SFML
	 */
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
		const Vector3d& getInverseAxisX() const;
		const Vector3d& getInverseAxisY() const;
		const Vector3d& getInverseAxisZ() const;
		double getZNear() const;
		double getZFar() const;
		Vector3d ObjectspaceToDrawspace(const Vector3d& v);
		Vector3d DrawspaceToObjectspace(const Vector3d& v);

	private:
		void calculateInverseMatrix();
		Vector3d m_position, m_x, m_y, m_z;
		Vector3d m_x_inverse, m_y_inverse, m_z_inverse;
		double m_zn, m_zf;
	};
}
#endif