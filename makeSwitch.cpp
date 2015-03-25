#include "makeObjects.h"
#include <iostream>

void makeSwitch(const Tmx::Map* map, int obj_grp, int obj_id)
{
	struct Data
	{
		bool player_touching = false;
	};
	Data* data = new Data;
	const Tmx::Object* obj = map->GetObjectGroup(obj_grp)->GetObject(obj_id);
	int z_index = map->GetObjectGroup(obj_grp)->GetZOrder();
	auto collisions = new hb::CollisionComponent(hb::Vector2d(1, 1));
	int gid = obj->GetGid();
	const Tmx::Tileset *tileset = map->FindTileset(gid);
	hb::Texture tex = hb::Texture::loadFromFile("res/levels/" + tileset->GetImage()->GetSource(), hb::Rect(0, 0, tileset->GetImage()->GetWidth(), tileset->GetImage()->GetHeight()));
	hb::Sprite sprite = hb::Sprite(tex, hb::Vector2d(tileset->GetTileWidth(), tileset->GetTileHeight()), hb::Vector2d(tileset->GetMargin(), tileset->GetMargin()));
	hb::FunctionComponent* fc = new hb::FunctionComponent();
	SwitchComponent* sc = new SwitchComponent(obj->GetProperties().GetStringProperty("target"));
	sc->setAction([=](hb::GameObject* target)
	{
		if (sc->isOn())
		{
			target->setActive(true);
		}
	});
	auto go = new hb::GameObject
	{
		collisions,
		new hb::SpriteComponent(sprite, {gid - tileset->GetFirstGid()}),
		fc,
		sc
	};

	go->setName(obj->GetType());
	hb::Vector3d v = obj->GetX() * hb::Renderer::getCamera().getInverseAxisX() + obj->GetY() * hb::Renderer::getCamera().getInverseAxisY() + z_index * hb::Renderer::getCamera().getInverseAxisZ();
	v.y -= 1;
	v.z += obj->GetProperties().GetIntProperty("z");
	go->setPosition(v);

	auto listener = hb::InputManager::instance()->listen([=](const hb::KeyPressed& e)
	{
		if (e.code == hb::Keyboard::Key::Space and data->player_touching)
		{
			sc->doSwitch();
		}
	});

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

	fc->setDestroyFunction([=]()
	{
		delete data;
		hb::InputManager::instance()->ignore(listener);
	});
}