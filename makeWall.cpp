#include "makeObjects.h"

void makeWall(const Tmx::Map* map, int obj_grp, int obj_id)
{
	const Tmx::Object* obj = map->GetObjectGroup(obj_grp)->GetObject(obj_id);
	int z_index = map->GetObjectGroup(obj_grp)->GetZOrder();
	//hb::Texture tex = hb::Texture::loadFromFile("");
	//tex.fill(hb::Rect(16, 16, 32, 32), hb::Color(142, 68, 173));
	//tex.stroke(hb::Vector2d(16, 16), hb::Vector2d(48, 48), hb::Color(192, 57, 43));
	//tex.repeat(true);
	auto collisions = new hb::CollisionComponent(hb::Vector2d(obj->GetWidth()/16., obj->GetHeight()/16.));

	auto wall = new hb::GameObject
	{
		collisions
	};

	wall->setName("Wall");
	//sprite->setPosition(hb::Vector3d(-size.x/2,size.y/2,0));
	hb::Vector3d v = obj->GetX() * hb::Renderer::getCamera().getInverseAxisX() + obj->GetY() * hb::Renderer::getCamera().getInverseAxisY() + z_index * hb::Renderer::getCamera().getInverseAxisZ();
	wall->setPosition(v);
}