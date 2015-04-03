#ifndef HB_CONTACT_LISTENER_2D_H
#define HB_CONTACT_LISTENER_2D_H
#include <Box2D/Box2D.h>
#include "../Core/DataRepository.h"
#include "../Core/GameObject.h"


namespace hb
{
	class ContactListener2d : public b2ContactListener
	{
	public:
		void BeginContact(b2Contact* contact)
		{
			b2Fixture* fixture_a = contact->GetFixtureA();
			b2Fixture* fixture_b = contact->GetFixtureB();
			GameObject* go_a = static_cast<GameObject*>(fixture_a->GetUserData());
			GameObject* go_b = static_cast<GameObject*>(fixture_b->GetUserData());
			DataRepository data_a;
			DataRepository data_b;
			data_a.setPointer("other", go_b);
			data_a.setPointer("fixture", fixture_a);
			data_a.setPointer("otherFixture", fixture_b);
			data_b.setPointer("other", go_a);
			data_b.setPointer("fixture", fixture_b);
			data_b.setPointer("otherFixture", fixture_a);
			go_a->getMessageManager().message("collisionStart", data_a);
			go_b->getMessageManager().message("collisionStart", data_b);
		}
		void EndContact(b2Contact* contact)
		{
			b2Fixture* fixture_a = contact->GetFixtureA();
			b2Fixture* fixture_b = contact->GetFixtureB();
			GameObject* go_a = static_cast<GameObject*>(fixture_a->GetUserData());
			GameObject* go_b = static_cast<GameObject*>(fixture_b->GetUserData());
			DataRepository data_a;
			DataRepository data_b;
			data_a.setPointer("other", go_b);
			data_b.setPointer("other", go_a);
			go_a->getMessageManager().message("collisionEnd", data_a);
			go_b->getMessageManager().message("collisionEnd", data_b);
		}
		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
		{ /* handle pre-solve event */ }
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
		{ /* handle post-solve event */ }
	};
}
#endif