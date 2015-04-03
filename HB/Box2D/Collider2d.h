#ifndef HB_COLLIDER2D_H
#define HB_COLLIDER2D_H
#include <Box2D/Box2D.h>
#include "Material2d.h"

namespace hb
{
	class RigidBody2dComponent;

	class Collider2d
	{
	public:
		friend class RigidBody2dComponent;

		~Collider2d()
		{
			delete m_shape;
		}

		void setName(const std::string& name)
		{
			m_name = name;
		}
	
	protected:
		Collider2d():
		m_is_sensor(false),
		m_material(),
		m_shape(nullptr)
		{};
		virtual b2FixtureDef getFixtureDef() const
		{
			b2FixtureDef fixture_def;
			fixture_def.shape = m_shape;
			fixture_def.friction = m_material.friction;
			fixture_def.restitution = m_material.bounciness;
			fixture_def.density = m_material.density;
			fixture_def.isSensor = m_is_sensor;
			return fixture_def;
		}

		bool m_is_sensor;
		std::string m_name;
		Material2d m_material;
		b2Shape* m_shape;
	};
}
#endif