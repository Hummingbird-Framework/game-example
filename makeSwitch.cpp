#include "makeObjects.h"
#include <iostream>

void makeSwitch(const Tmx::Map* map, int obj_grp, int obj_id)
{
	// Define GameObject status data and instantiate it
	struct Data
	{
		bool player_touching = false;
	};
	Data* data = new Data;
	// Get Tmx object representing the new Switch GameObject
	const Tmx::Object* obj = map->GetObjectGroup(obj_grp)->GetObject(obj_id);
	// Get z position from s-index of ObjectGroup
	int z_index = map->GetObjectGroup(obj_grp)->GetZOrder();
	auto collisions = new hb::CollisionComponent(hb::Vector2d(1, 1));
	// Make sprite from tile
	int gid = obj->GetGid();
	const Tmx::Tileset *tileset = map->FindTileset(gid);
	hb::Texture tex = hb::Texture::loadFromFile("res/levels/" + tileset->GetImage()->GetSource(), hb::Rect(0, 0, tileset->GetImage()->GetWidth(), tileset->GetImage()->GetHeight()));
	hb::Sprite sprite = hb::Sprite(tex, hb::Vector2d(tileset->GetTileWidth(), tileset->GetTileHeight()), hb::Vector2d(tileset->GetMargin(), tileset->GetMargin()));

	// Define Function component
	hb::FunctionComponent* fc = new hb::FunctionComponent();
	// Define Switch component
	SwitchComponent* sc = new SwitchComponent(obj->GetProperties().GetStringProperty("target"));
	sc->setAction([=](hb::GameObject* target)
	{
		if (sc->isOn())
		{
			target->setActive(true);
		}
	});
	// Create new GameObject
	auto go = new hb::GameObject
	{
		collisions,
		new hb::SpriteComponent(sprite, {gid - tileset->GetFirstGid()}),
		fc,
		sc
	};
	// Set name and position
	go->setName(obj->GetType());
	hb::Vector3d v = obj->GetX() * hb::Renderer::getCamera().getInverseAxisX() + obj->GetY() * hb::Renderer::getCamera().getInverseAxisY() + z_index * hb::Renderer::getCamera().getInverseAxisZ();
	v.y -= 1;
	v.z += obj->GetProperties().GetIntProperty("z");
	go->setPosition(v);

	// Input listener to activate switch
	auto listener = hb::InputManager::instance()->listen([=](const hb::KeyPressed& e)
	{
		if (e.code == hb::Keyboard::Key::Space and data->player_touching)
		{
			sc->doSwitch();
		}
	});

	// GameObject update function
	fc->setUpdateFunction([=]()
	{
		bool t = false;
		while (not collisions->empty())
		{
			auto c = collisions->nextCollision();
			t |= (c.object->getName() == "Player");
		}
		data->player_touching = t;
	});

	// GameObject destroy function
	fc->setDestroyFunction([=]()
	{
		delete data;
		hb::InputManager::instance()->ignore(listener);
	});
}
