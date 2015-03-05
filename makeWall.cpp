#include "makeObjects.h"

hb::GameObject* makeWall(hb::RenderWindowManager* window_manager, const hb::Vector2d& position, const hb::Vector2d& size)
{
	hb::Texture tex = hb::Texture(hb::TextureManager::instance()->get(hb::TextureManager::instance()->getT404()), hb::TextureManager::makeTexId("t404moded", sf::IntRect()));
	tex.fill(hb::Rect(16, 16, 32, 32), hb::Color(142, 68, 173));
	tex.stroke(hb::Vector2d(16, 16), hb::Vector2d(48, 48), hb::Color(192, 57, 43));
	tex.repeat(true);

	auto wall = new hb::GameObject
	{
		new hb::CollisionComponent(size),
		new hb::SpriteComponent(window_manager, tex),
		new hb::FunctionComponent()
	};

	wall->setName("Wall");
	auto sprite = wall->getComponent<hb::SpriteComponent>();
	sprite->getSprite().setFrameSize(size);
	sprite->setPosition(hb::Vector3d(0,0,0));
	wall->setPosition(hb::Vector3d(position, 0));

	auto fc = wall->getComponent<hb::FunctionComponent>();
	fc->run([fc]()
	{
		hb::InputManager::ListenerId<hb::MouseButtonWorld>* mousebuttonworld_listener_id = new hb::InputManager::ListenerId<hb::MouseButtonWorld>();
		*mousebuttonworld_listener_id = hb::InputManager::instance()->listen([fc](const hb::MouseButtonWorld& e)
		{
			fc->getGameObject()->setPosition(hb::Vector3d(e.x, e.y, fc->getGameObject()->getPosition().z));
		});

		fc->setPointer("mousebuttonworld_listener_id", mousebuttonworld_listener_id);
	});
	fc->setDestroyFunction([fc]()
	{
		hb::InputManager::instance()->ignore(*fc->getPointer<hb::InputManager::ListenerId<hb::MouseButtonWorld>>("mousebuttonworld_listener_id"));
	});

	return wall;
}