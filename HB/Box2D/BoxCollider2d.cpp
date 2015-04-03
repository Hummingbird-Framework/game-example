#include "BoxCollider2d.h"
using namespace hb;

BoxCollider2d::BoxCollider2d(const Material2d& material, const Vector2d& size, const Vector2d& center, double angle, bool is_sensor):
Collider2d::Collider2d()
{
	m_material = material;
	m_is_sensor = is_sensor;
	b2PolygonShape* box = new b2PolygonShape();
	box->SetAsBox(size.x/2., size.y/2., b2Vec2(center.x, center.y), degToRad(angle));
	m_shape = box;
}
