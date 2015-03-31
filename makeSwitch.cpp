#include "makeObjects.h"
#include <iostream>

void makeSwitch(hb::GameObject* go, const Tmx::Map* map, int obj_grp, int obj_id)
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
	auto collisions = new hb::CollisionComponent(hb::Vector2d(1, 1));
	// Make sprite from tile
	int gid = obj->GetGid();
	const Tmx::Tileset *tileset = map->FindTileset(gid);
	hb::Texture tex = hb::Texture::loadFromFile("res/levels/" + tileset->GetImage()->GetSource(), hb::Rect(0, 0, tileset->GetImage()->GetWidth(), tileset->GetImage()->GetHeight()));
	hb::Sprite sprite = hb::Sprite(tex, hb::Vector2d(tileset->GetTileWidth(), tileset->GetTileHeight()), hb::Vector2d(tileset->GetMargin(), tileset->GetMargin()));

	// Define Function component
	hb::FunctionComponent* fc = new hb::FunctionComponent();
	// Define Switch component
	std::string tmp;
	std::stringstream ss;
	ss << obj->GetProperties().GetStringProperty("target");
	std::vector<int> targets;
	int target_id;
	while(ss >> target_id)
	{
		targets.push_back(target_id);
	}
	SwitchComponent* sc = new SwitchComponent(targets);
	sc->setAction([=](hb::GameObject* target)
	{
		target->setActive(sc->isOn());
	});
	// Create new GameObject
	go->addComponents({
		collisions,
		new hb::SpriteComponent(sprite, {gid - tileset->GetFirstGid()}),
		fc,
		sc
	});
	hb::Vector3d v = go->getPosition();
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
