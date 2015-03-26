#include "makeObjects.h"

void makeBridge(const Tmx::Map* map, int obj_grp, int obj_id)
{
	// Get Tmx object representing the new Door GameObject
	const Tmx::Object* obj = map->GetObjectGroup(obj_grp)->GetObject(obj_id);
	// Get z position from Tmx layer z-index
	int z_index = map->GetObjectGroup(obj_grp)->GetZOrder();
	// Make sprite from object tile
	int gid = obj->GetGid();
	const Tmx::Tileset *tileset = map->FindTileset(gid);
	hb::Texture tex = hb::Texture::loadFromFile("res/levels/" + tileset->GetImage()->GetSource(), hb::Rect(0, 0, tileset->GetImage()->GetWidth(), tileset->GetImage()->GetHeight()));
	hb::Sprite sprite = hb::Sprite(tex, hb::Vector2d(tileset->GetTileWidth(), tileset->GetTileHeight()), hb::Vector2d(tileset->GetMargin(), tileset->GetMargin()));

	// Create new GameObject with components previously defined
	auto go = new hb::GameObject
	{
		new hb::SpriteComponent(sprite, {gid - tileset->GetFirstGid()}),
		new hb::CollisionComponent(hb::Vector2d(0.8, 0.9))
	};
	// Disable GameObject 
	go->setActive(false);
	go->setName(obj->GetName());
	// Set GameObject position
	hb::Vector3d v = obj->GetX() * hb::Renderer::getCamera().getInverseAxisX() + obj->GetY() * hb::Renderer::getCamera().getInverseAxisY() + z_index * hb::Renderer::getCamera().getInverseAxisZ();
	v.y -= 1;
	// Get relative z position from Tile defined properties
	v.z += obj->GetProperties().GetIntProperty("z");
	go->setPosition(v);
}
