#include "RigidBody2dComponent.h"
using namespace hb;


unsigned int RigidBody2dComponent::s_fixtures_count = 0;


RigidBody2dComponent::RigidBody2dComponent(const b2BodyDef& definition):
m_b2body(Physics2d::getB2World()->CreateBody(&definition)),
m_fixtures_data()
{

}

RigidBody2dComponent::~RigidBody2dComponent()
{
	Physics2d::getB2World()->DestroyBody(m_b2body);
	for(Fixture2dData* f : m_fixtures_data)
		delete f;
}


void RigidBody2dComponent::init()
{
	m_b2body->SetUserData(getGameObject());
}


void RigidBody2dComponent::update()
{
	double z = getGameObject()->getPosition().z;
	getGameObject()->setPosition(m_b2body->GetPosition().x, m_b2body->GetPosition().y, z);
	Vector3d rot = getGameObject()->getRotation();
	getGameObject()->setRotation(rot.x, rot.y, radToDeg(m_b2body->GetAngle()));
}


int RigidBody2dComponent::addCollider(const Collider2d& collider)
{
	b2FixtureDef def = collider.getFixtureDef();
	Fixture2dData* data = new Fixture2dData;
	m_fixtures_data.push_back(data);
	data->id = s_fixtures_count++;
	data->name = collider.m_name;
	data->rigid_body = this;
	def.userData = data;
	m_b2body->CreateFixture(&def);
	return data->id;
}


b2Body* RigidBody2dComponent::getB2Body()
{
	return m_b2body;
}
