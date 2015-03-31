#include "makeObjects.h"

void makeWall(hb::GameObject* wall, const Tmx::Map* map, int obj_grp, int obj_id)
{
	// Get Tmx object representing the new Wall GameObject
	const Tmx::Object* obj = map->GetObjectGroup(obj_grp)->GetObject(obj_id);
	int z_index = map->GetObjectGroup(obj_grp)->GetZOrder();
	// Define collision component
	auto collisions = new hb::CollisionComponent(hb::Vector2d(obj->GetWidth()/16., obj->GetHeight()/16.));

	// Create GameObject
	wall->addComponents({
		collisions
	});

	hb::Vector3d v = obj->GetX() * hb::Renderer::getCamera().getInverseAxisX() + obj->GetY() * hb::Renderer::getCamera().getInverseAxisY() + z_index * hb::Renderer::getCamera().getInverseAxisZ();
	wall->setPosition(v);
}
