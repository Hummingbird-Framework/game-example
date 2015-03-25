#include "makeObjects.h"
#include <iostream>

void makeDoor(const Tmx::Map* map, int obj_grp, int obj_id)
{
	const Tmx::Object* object = map->GetObjectGroup(obj_grp)->GetObject(obj_id);
	hb::Vector3d position = hb::Renderer::getCamera().DrawspaceToObjectspace(hb::Vector3d(object->GetX(), object->GetY(), map->GetObjectGroup(obj_grp)->GetZOrder()));
	--position.y;
	int gid = object->GetGid();
	const Tmx::Tileset* tileset = map->FindTileset(gid);
	hb::Texture tex = hb::Texture::loadFromFile("res/levels/" + tileset->GetImage()->GetSource());
	hb::Sprite sprite(tex, hb::Vector2d(tileset->GetTileWidth(), tileset->GetTileHeight()));

	hb::CollisionComponent* collisions = new hb::CollisionComponent(1, 1);
	hb::FunctionComponent* fc = new hb::FunctionComponent;

	std::string target = object->GetProperties().GetStringProperty("target");

	struct Data
	{
		bool touching_player = false;
	};

	Data* data = new Data;

	fc->setUpdateFunction([=]()
	{
		bool t = false;
		while (not collisions->empty())
		{
			auto c = collisions->nextCollision();
			t |= (c.object->getName() == "Player");
			std::cout << "tocando" << std::endl;
		}
		data->touching_player = t;
	});

	auto listener = hb::InputManager::instance()->listen([=](const hb::KeyPressed& ev)
	{
		if (ev.code == hb::Keyboard::Key::Space and data->touching_player)
		{
			hb::Game::setScene(target);
		}
	});

	fc->setDestroyFunction([=]()
	{
		delete data;
		hb::InputManager::instance()->ignore(listener);
	});

	auto obj = new hb::GameObject
	{
		new hb::SpriteComponent(sprite, {gid - tileset->GetFirstGid()}),
		collisions,
		fc
	};
	obj->setPosition(position);
	obj->setName("Door");
}