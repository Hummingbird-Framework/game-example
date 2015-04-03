#ifndef HB_RIGIDBODY2D_COMPONENT_H
#define HB_RIGIDBODY2D_COMPONENT_H
#include <vector>
#include <Box2D/Box2D.h>
#include "../Core/GameObject.h"
#include "Physics2d.h"
#include "Collider2d.h"
#include "Fixture2dData.h"

namespace hb
{
	class RigidBody2dComponent : public GameObject::Component
	{
	public:
		RigidBody2dComponent(const b2BodyDef& definition);
		~RigidBody2dComponent();

		void init() override;
		void update() override;

		int addCollider(const Collider2d& collider);

		b2Body* getB2Body();
	
	private:
		static unsigned int s_fixtures_count;

		b2Body* m_b2body;
		std::vector<Fixture2dData*> m_fixtures_data;
	};
}
#endif