#include "ContactListener2d.h"
using namespace hb;

void ContactListener2d::BeginContact(b2Contact* contact)
{
	b2Fixture* fixture_a = contact->GetFixtureA();
	b2Fixture* fixture_b = contact->GetFixtureB();

	GameObject* go_a = static_cast<GameObject*>(fixture_a->GetBody()->GetUserData());
	GameObject* go_b = static_cast<GameObject*>(fixture_b->GetBody()->GetUserData());

	DataRepository data_a;
	DataRepository data_b;

	packData(fixture_a, fixture_b, data_a, data_b);

	if (fixture_a->IsSensor())
		go_a->sendMessage("sensorStart", data_a);
	else
		go_a->sendMessage("collisionStart", data_a);

	if (fixture_b->IsSensor())
		go_b->sendMessage("sensorStart", data_b);
	else
		go_b->sendMessage("collisionStart", data_b);

	unsigned int id_a = static_cast<Fixture2dData*>(fixture_a->GetUserData())->id;
	unsigned int id_b = static_cast<Fixture2dData*>(fixture_b->GetUserData())->id;
	
	ContactId contact_id(std::min(id_a, id_b), std::max(id_a, id_b));
	m_current_collisions.insert(ContactSetData(contact_id, ContactInfo{fixture_a, fixture_b}));
}


void ContactListener2d::EndContact(b2Contact* contact)
{
	b2Fixture* fixture_a = contact->GetFixtureA();
	b2Fixture* fixture_b = contact->GetFixtureB();

	GameObject* go_a = static_cast<GameObject*>(fixture_a->GetBody()->GetUserData());
	GameObject* go_b = static_cast<GameObject*>(fixture_b->GetBody()->GetUserData());

	DataRepository data_a;
	DataRepository data_b;

	packData(fixture_a, fixture_b, data_a, data_b);

	if (fixture_a->IsSensor())
		go_a->sendMessage("sensorEnd", data_a);
	else
		go_a->sendMessage("collisionEnd", data_a);

	if (fixture_b->IsSensor())
		go_b->sendMessage("sensorEnd", data_b);
	else
		go_b->sendMessage("collisionEnd", data_b);
	
	unsigned int id_a = static_cast<Fixture2dData*>(fixture_a->GetUserData())->id;
	unsigned int id_b = static_cast<Fixture2dData*>(fixture_b->GetUserData())->id;

	m_current_collisions.erase(ContactId(std::min(id_a, id_b), std::max(id_a, id_b)));
}


void ContactListener2d::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{ /* handle pre-solve event */ }


void ContactListener2d::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{ /* handle post-solve event */ }


void ContactListener2d::sendStayContact()
{
	for (std::unordered_map<std::pair<int, int>, ContactInfo>::iterator it = m_current_collisions.begin(); it != m_current_collisions.end(); ++it)
	{
		ContactInfo& contact = it->second;
		b2Fixture* fixture_a = contact.fixture_a;
		b2Fixture* fixture_b = contact.fixture_b;

		GameObject* go_a = static_cast<GameObject*>(fixture_a->GetBody()->GetUserData());
		GameObject* go_b = static_cast<GameObject*>(fixture_b->GetBody()->GetUserData());

		DataRepository data_a;
		DataRepository data_b;

		packData(fixture_a, fixture_b, data_a, data_b);

		if (fixture_a->IsSensor())
			go_a->sendMessage("sensorStay", data_a);
		else
			go_a->sendMessage("collisionStay", data_a);

		if (fixture_b->IsSensor())
			go_b->sendMessage("sensorStay", data_b);
		else
			go_b->sendMessage("collisionStay", data_b);
	}
}


void ContactListener2d::packData(b2Fixture* fixture_a, b2Fixture* fixture_b, DataRepository& data_a, DataRepository& data_b)
{
	data_a.setPointer("other", static_cast<GameObject*>(fixture_b->GetBody()->GetUserData()));
	data_a.setPointer("fixture", fixture_a);
	data_a.setPointer("otherFixture", fixture_b);
	data_a.setPointer("fixtureData", static_cast<Fixture2dData*>(fixture_a->GetUserData()));
	data_a.setPointer("otherFixtureData", static_cast<Fixture2dData*>(fixture_b->GetUserData()));
	
	data_b.setPointer("other", static_cast<GameObject*>(fixture_a->GetBody()->GetUserData()));
	data_b.setPointer("fixture", fixture_b);
	data_b.setPointer("otherFixture", fixture_a);
	data_b.setPointer("fixtureData", static_cast<Fixture2dData*>(fixture_b->GetUserData()));
	data_b.setPointer("otherFixtureData", static_cast<Fixture2dData*>(fixture_a->GetUserData()));
}