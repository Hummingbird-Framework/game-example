#include "makeObjects.h"

void makeDynamicBody(hb::GameObject* go, const Tmx::Map* map, int obj_grp, int obj_id)
{
	const Tmx::Object* obj = map->GetObjectGroup(obj_grp)->GetObject(obj_id);
	b2BodyDef body_def;
	body_def.type = b2_dynamicBody;
	body_def.position = b2Vec2(go->getPosition().x+0.5, go->getPosition().y-0.5);
	body_def.linearDamping = 0.1;
	auto rigid_body = new hb::RigidBody2dComponent(body_def);
	hb::Texture tex = hb::Texture::makeTexture(hb::Vector2d(obj->GetWidth(), obj->GetHeight()));
	tex.fill(hb::Rect(0,0,obj->GetWidth(), obj->GetHeight()), hb::Color(123, 172, 16));
	hb::Sprite spr(tex);
	spr.setCenter(hb::Vector2d(obj->GetWidth()/2.,obj->GetHeight()/2.));
	auto spr_comp = new hb::SpriteComponent(spr);
	spr_comp->setRotation(hb::Vector3d(0,0,obj->GetRot()));
	go->addComponents({
		rigid_body,
		spr_comp
	});

	hb::Material2d mat;
	mat.friction = obj->GetProperties().GetFloatProperty("friction", 0.);
	mat.bounciness = obj->GetProperties().GetFloatProperty("bounciness", 0.);
	mat.density = obj->GetProperties().GetFloatProperty("density", 1.);
	if (obj->GetEllipse() != 0)
	{
		hb::CircleCollider2d collider(
			mat,
			hb::Vector2d(),
			obj->GetWidth()/64.,
			false);
		rigid_body->addCollider(collider);

	}
	else
	{
		hb::BoxCollider2d collider(
			mat,
			hb::Vector2d(obj->GetWidth()/32., obj->GetHeight()/32.),
			hb::Vector2d(),
			obj->GetRot(),
			false);
		rigid_body->addCollider(collider);
	}
}