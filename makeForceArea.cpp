#include "makeObjects.h"

void makeForceArea(hb::GameObject* go, const Tmx::Map* map, int obj_grp, int obj_id)
{
	const Tmx::Object* object = map->GetObjectGroup(obj_grp)->GetObject(obj_id);
	b2BodyDef def;
	def.position = b2Vec2(go->getPosition().x + object->GetWidth()/64., go->getPosition().y + object->GetHeight()/64.);
	auto rigid_body = new hb::RigidBody2dComponent(def);
	hb::Material2d mat;
	mat.friction = object->GetProperties().GetFloatProperty("friction", 0.);
	mat.bounciness = object->GetProperties().GetFloatProperty("bounciness", 0.);
	mat.density = object->GetProperties().GetFloatProperty("density", 1.);
	if (object->GetEllipse() != 0)
	{
		hb::CircleCollider2d collider(
			mat,
			hb::Vector2d(),
			object->GetWidth()/64.,
			true);
		rigid_body->addCollider(collider);

	}
	else
	{
		hb::BoxCollider2d collider(
			mat,
			hb::Vector2d(object->GetWidth()/32., object->GetHeight()/32.),
			hb::Vector2d(),
			object->GetRot(),
			true);
		rigid_body->addCollider(collider);
	}

	auto fc = new hb::FunctionComponent();
	go->addComponents({rigid_body, fc});

	b2Vec2 force (object->GetProperties().GetFloatProperty("force_x", 0.0), object->GetProperties().GetFloatProperty("force_y", 0.0));
	fc->addListener("sensorStay", [=](hb::DataRepository& data)
		{
			b2Body* other_body = data.getPointer<b2Fixture>("otherFixture")->GetBody();
			other_body->ApplyForceToCenter(force, true);
		});
}