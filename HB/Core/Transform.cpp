#include "Transform.h"
using namespace hb;

Transform::Transform():
m_position(Vector3d()),
m_scale(Vector3d(1, 1, 1)),
m_rotation_angle(Vector3d())
{}


Transform::Transform(const Vector3d& init_pos):
m_position(init_pos),
m_scale(Vector3d(1, 1, 1)),
m_rotation_angle(Vector3d())
{}


Transform::~Transform()
{}


const Vector3d& Transform::getPosition() const
{
	return m_position;
}


void Transform::setPosition(const Vector3d& position)
{
	m_position = position;
}


void Transform::setPosition(double p_x, double p_y, double p_z)
{
	setPosition(hb::Vector3d(p_x, p_y, p_z));
}


const Vector3d& Transform::getRotation() const
{
	return m_rotation_angle;
}


void Transform::setRotation(const Vector3d& angle)
{
	m_rotation_angle = angle;
}


void Transform::setRotation(double rotation_x, double rotation_y, double rotation_z)
{
	setRotation(hb::Vector3d(rotation_x, rotation_y, rotation_z));
}


const Vector3d& Transform::getScale() const
{
	return m_scale;
}


void Transform::setScale(const Vector3d& scale)
{
	m_scale = scale;
}


void Transform::setScale(double scale_x, double scale_y, double scale_z)
{
	setScale(hb::Vector3d(scale_x, scale_y, scale_z));
}
