#ifndef HB_CONTACT_LISTENER_2D_H
#define HB_CONTACT_LISTENER_2D_H
#include <unordered_map>
#include <Box2D/Box2D.h>
#include "../Core/DataRepository.h"
#include "../Core/GameObject.h"
#include "Fixture2dData.h"
#include "hash_pair.h"

////////////////////////////////////////
// Messages:
//   "collisionStart": when an incomming collider makes contact with a collider of the reciever GameObject
//   "collisionStay": sent each frame that a collider makes contact with a collider of the reciever GameObject
//   "collisionEnd": when a collider stops touching a collider of the reciever GameObject
//   "sensorStart": when an incomming collider makes contact with a sensor collider of the reciever GameObject
//   "sensorStay": sent each frame that a collider makes contact with a sensor collider of the reciever GameObject
//   "sensorEnd": when a collider stops touching a sensor collider of the reciever GameObject
//
// Message content:
//   "other": incoming GameObject
//   "fixture": fixture of listener GameObject
//   "otherFixture": fixture of incoming GameObject
//   "fixtureData": Fixture2dData of fixture of listener object
//   "otherFixtureData": Fixture2dData of fixture of incoming object
////////////////////////////////////////

namespace hb
{
	class ContactListener2d : public b2ContactListener
	{
	public:
		void BeginContact(b2Contact* contact);
		void EndContact(b2Contact* contact);
		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

		void sendStayContact();

	private:
		struct ContactInfo
		{
			b2Fixture* fixture_a;
			b2Fixture* fixture_b;
		};
		typedef std::pair<int, int> ContactId;
		typedef std::pair<ContactId, ContactInfo> ContactSetData;

		static void packData(b2Fixture* fixture_a, b2Fixture* fixture_b, DataRepository& data_a, DataRepository& data_b);

		std::unordered_map<std::pair<int, int>, ContactInfo> m_current_collisions;
	};
}
#endif