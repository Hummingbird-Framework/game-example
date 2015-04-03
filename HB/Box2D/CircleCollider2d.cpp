#include "CircleCollider2d.h"
using namespace hb;

CircleCollider2d::CircleCollider2d(const Material2d& material, const Vector2d& center, double radius, bool is_sensor):
Collider2d::Collider2d()
{
	m_material = material;
	m_is_sensor = is_sensor;
	b2CircleShape* circle = new b2CircleShape();
	circle->m_radius = radius;
	circle->m_p = b2Vec2(center.x, center.y);
	m_shape = circle;
}
