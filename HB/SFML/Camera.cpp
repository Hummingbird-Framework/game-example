#include "Camera.h"
#include <iostream>
using namespace hb;


Camera::Camera():
m_position(),
m_x(1, 0, 0),
m_y(0, 1, 0),
m_z(0, 0, 1),
m_zn(-100.),
m_zf(100.)
{

}


Camera::~Camera()
{

}


void Camera::setPosition(const Vector3d& pos)
{
	m_position = pos.normalized();
}


void Camera::setAxisX(const Vector3d& x)
{
	m_x = x.normalized();
}


void Camera::setAxisY(const Vector3d& y)
{
	m_y = y.normalized();
}


void Camera::setAxisZ(const Vector3d& z)
{
	m_z = z.normalized();
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


double Camera::getZNear() const
{
	return m_zn;
}


double Camera::getZFar() const
{
	return m_zf;
}
