#include "makeObjects.h"
#include <iostream>

void makeDoor(hb::GameObject* go, const Tmx::Map* map, int obj_grp, int obj_id)
{
	// Get Tmx object representing the new Door GameObject
	const Tmx::Object* object = map->GetObjectGroup(obj_grp)->GetObject(obj_id);
	// Get it's position in object space
	hb::Vector3d position = hb::Renderer::getCamera().DrawspaceToObjectspace(hb::Vector3d(object->GetX(), object->GetY(), map->GetObjectGroup(obj_grp)->GetZOrder()));
	// Fixe Tiled position bug for Tile objects
	--position.y;
	// Make sprite from object tile
	int gid = object->GetGid();
	const Tmx::Tileset* tileset = map->FindTileset(gid);
	hb::Texture tex = hb::Texture::loadFromFile("res/levels/" + tileset->GetImage()->GetSource());
	hb::Sprite sprite(tex, hb::Vector2d(tileset->GetTileWidth(), tileset->GetTileHeight()));

	// Initialize collision component
	hb::CollisionComponent* collisions = new hb::CollisionComponent(hb::Vector2d(1, 1));
	// Initialize function component
	hb::FunctionComponent* fc = new hb::FunctionComponent;

	// Get Door target (defined as a property in Tiled)
	std::string target = object->GetProperties().GetStringProperty("target");

	// Define GameObject status data and instantiate it
	struct Data
	{
		bool touching_player = false;
	};
	Data* data = new Data;

	// Define Door update function
	fc->setUpdateFunction([=]()
	{
		// detect if touching player
		bool t = false;
		while (not collisions->empty())
		{
			auto c = collisions->nextCollision();
			t |= (c.object->getName() == "Player");
		}
		data->touching_player = t;
	});

	// Define input listener for activating Door
	auto listener = hb::InputManager::instance()->listen([=](const hb::KeyPressed& ev)
	{
		if (ev.code == hb::Keyboard::Key::Space and data->touching_player)
		{
			hb::Game::setScene(target);
		}
	});

	// Function called when object is about to be destroyed
	fc->setDestroyFunction([=]()
	{
		// Release memory used by data
		delete data;
		// No longer listen to event
		hb::InputManager::instance()->ignore(listener);
	});
	
	// Create new GameObject with components previously defined
	go->addComponents({
		new hb::SpriteComponent(sprite, {gid - tileset->GetFirstGid()}),
		collisions,
		fc
	});
}
