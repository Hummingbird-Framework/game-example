#include "Camera.h"
using namespace hb;


Camera::Camera():
m_position(),
m_x(1, 0, 0),
m_y(0, 1, 0),
m_z(0, 0, 1),
m_zn(-10000.),
m_zf(10000.)
{
	calculateInverseMatrix();
}


Camera::~Camera()
{

}


void Camera::setPosition(const Vector3d& pos)
{
	m_position = pos;
}


void Camera::setAxisX(const Vector3d& x)
{
	m_x = x;
	calculateInverseMatrix();
}


void Camera::setAxisY(const Vector3d& y)
{
	m_y = y;
	calculateInverseMatrix();
}


void Camera::setAxisZ(const Vector3d& z)
{
	m_z = z;
	calculateInverseMatrix();
}


void Camera::setZNear(double zn)
{
	m_zn = zn;
}


void Camera::setZFar(double zf)
{
	m_zf = zf;
}


const Vector3d& Camera::getPosition() const
{
	return m_position;
}


const Vector3d& Camera::getAxisX() const
{
	return m_x;
}


const Vector3d& Camera::getAxisY() const
{
	return m_y;
}


const Vector3d& Camera::getAxisZ() const
{
	return m_z;
}


const Vector3d& Camera::getInverseAxisX() const
{
	return m_x_inverse;
}


const Vector3d& Camera::getInverseAxisY() const
{
	return m_y_inverse;
}


const Vector3d& Camera::getInverseAxisZ() const
{
	return m_z_inverse;
}


double Camera::getZNear() const
{
	return m_zn;
}


double Camera::getZFar() const
{
	return m_zf;
}


void Camera::calculateInverseMatrix()
{
	double determinant = + m_x.x * (m_y.y * m_z.z - m_z.y * m_y.z)
						 - m_x.y * (m_y.x * m_z.z - m_y.z * m_z.x)
						 + m_x.z * (m_y.x * m_z.y - m_y.y * m_z.x);
	hb_assert(determinant != 0., "The vectors defining the Drawspace are not linearly independent.");
	double invdet = 1/determinant;
	m_x_inverse.x =  (m_y.y * m_z.z - m_z.y * m_y.z) * invdet;
	m_x_inverse.y = -(m_x.y * m_z.z - m_x.z * m_z.y) * invdet;
	m_x_inverse.z =  (m_x.y * m_y.z - m_x.z * m_y.y) * invdet;
	m_y_inverse.x = -(m_y.x * m_z.z - m_y.z * m_z.x) * invdet;
	m_y_inverse.y =  (m_x.x * m_z.z - m_x.z * m_z.x) * invdet;
	m_y_inverse.z = -(m_x.x * m_y.z - m_y.x * m_x.z) * invdet;
	m_z_inverse.x =  (m_y.x * m_z.y - m_z.x * m_y.y) * invdet;
	m_z_inverse.y = -(m_x.x * m_z.y - m_z.x * m_x.y) * invdet;
	m_z_inverse.z =  (m_x.x * m_y.y - m_y.x * m_x.y) * invdet;
}


Vector3d Camera::ObjectspaceToDrawspace(const Vector3d& v)
{
	return (getAxisX() * v.x) + (getAxisY() * v.y) + (getAxisZ() * v.z);
}


Vector3d Camera::DrawspaceToObjectspace(const Vector3d& v)
{
	return (getInverseAxisX() * v.x) + (getInverseAxisY() * v.y) + (getInverseAxisZ() * v.z);
}
