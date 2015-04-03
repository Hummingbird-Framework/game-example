#include "makeObjects.h"

void makeWall(hb::GameObject* wall, const Tmx::Map* map, int obj_grp, int obj_id)
{
	// Get Tmx object representing the new Wall GameObject
	const Tmx::Object* obj = map->GetObjectGroup(obj_grp)->GetObject(obj_id);
	int z_index = map->GetObjectGroup(obj_grp)->GetZOrder();
	
	b2BodyDef body_def;
	body_def.position = b2Vec2(wall->getPosition().x, wall->getPosition().y);
	auto rigid_body = new hb::RigidBody2dComponent(body_def);
	hb::Material2d mat;
	mat.friction = obj->GetProperties().GetFloatProperty("friction", 0.);
	mat.bounciness = obj->GetProperties().GetFloatProperty("bounciness", 0.);
	mat.density = obj->GetProperties().GetFloatProperty("density", 1.);
	hb::BoxCollider2d box (
		mat,
		hb::Vector2d(obj->GetWidth()/16., obj->GetHeight()/16.),
		hb::Vector2d(obj->GetWidth()/32., obj->GetHeight()/32.),
		0.,
		false);

	rigid_body->addCollider(box);

	// Create GameObject
	wall->addComponents({
		rigid_body
	});

	hb::Vector3d v = obj->GetX() * hb::Renderer::getCamera().getInverseAxisX() + obj->GetY() * hb::Renderer::getCamera().getInverseAxisY() + z_index * hb::Renderer::getCamera().getInverseAxisZ();
	wall->setPosition(v);
}
