#include "makeObjects.h"

hb::GameObject* makeWall(const hb::Vector2d& position, const hb::Vector2d& size)
{
	hb::Texture tex = hb::Texture::loadFromFile("");
	//tex.fill(hb::Rect(16, 16, 32, 32), hb::Color(142, 68, 173));
	//tex.stroke(hb::Vector2d(16, 16), hb::Vector2d(48, 48), hb::Color(192, 57, 43));
	tex.repeat(true);
	auto collisions = new hb::CollisionComponent(size);

	auto wall = new hb::GameObject
	{
		collisions,
		new hb::SpriteComponent(tex),
		new hb::FunctionComponent()
	};

	wall->setName("Wall");
	auto sprite = wall->getComponent<hb::SpriteComponent>();
	sprite->getSprite().setFrameSize(size*32.);
	//sprite->setPosition(hb::Vector3d(-size.x/2,size.y/2,0));
	wall->setPosition(hb::Vector3d(position, -1));

	auto fc = wall->getComponent<hb::FunctionComponent>();

	/*hb::InputManager::ListenerId<hb::MouseButtonWorld> mousebuttonworld_listener_id = hb::InputManager::ListenerId<hb::MouseButtonWorld>();
	mousebuttonworld_listener_id = hb::InputManager::instance()->listen([=](const hb::MouseButtonWorld& e)
	{
		fc->getGameObject()->setPosition(hb::Vector3d(e.x, e.y, fc->getGameObject()->getPosition().z));
	});*/

	fc->setUpdateFunction([=]()
	{
		while(not collisions->empty())
		{
			auto c = collisions->nextCollision();
			auto go = c.object;
			if (go->getName() == "Fireball")
				wall->destroy();
		}
	});

	fc->setDestroyFunction([=]()
	{
		//hb::InputManager::instance()->ignore(mousebuttonworld_listener_id);
	});

	return wall;
}