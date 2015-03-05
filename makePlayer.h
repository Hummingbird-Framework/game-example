#include "HB/Base.h"
#include "HB/SFML.h"

hb::GameObject* makePlayer(hb::RenderWindowManager* window_manager1)
{
	// Define the player GameObject
	auto player = new hb::GameObject
	{
		new hb::SpriteComponent(window_manager1),
		new hb::CollisionComponent(hb::Vector2d(32, 32)),
		new hb::FunctionComponent()
	};

	// Set name
	player->setName("Player");

	// get the FunctionComponent we added in the definition
	auto fc = player->getComponent<hb::FunctionComponent>();

	// run initialization code (define variables and event callbacks)
	fc->run([fc] ()
	{
		fc->getGameObject()->setPosition(hb::Vector3d(100, 100, 0));
		fc->setPointer("direction", new hb::Vector2d());
		fc->setPointer("last_direction", new hb::Vector2d(0, -1));
		fc->setBool("running", false);
		fc->setPointer("player_sprite", fc->getGameObject()->getComponent<hb::SpriteComponent>());
		fc->setPointer("m_collision", fc->getGameObject()->getComponent<hb::CollisionComponent>());
		fc->setPointer("last_position", new hb::Vector3d(fc->getGameObject()->getPosition()));

		hb::Texture tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
		fc->setPointer("sprite_down", new hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d(), 0, 2, hb::Time::seconds(0.3)));
		tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
		fc->setPointer("sprite_left", new hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d(), 3, 5, hb::Time::seconds(0.3)));
		tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
		fc->setPointer("sprite_right", new hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d(), 6, 8, hb::Time::seconds(0.3)));
		tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
		fc->setPointer("sprite_up", new hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d(), 9, 11, hb::Time::seconds(0.3)));

		fc->getPointer<hb::SpriteComponent>("player_sprite")->setSprite(*fc->getPointer<hb::Sprite>("sprite_down"));

		auto keypressed_listener_id = hb::InputManager::instance()->listen(
		[fc](const hb::KeyPressed& event)
		{
			int value = 1;

			sf::Keyboard::Key code = event.code;
			if (code == sf::Keyboard::Key::W and (*fc->getPointer<hb::Vector2d>("direction")).y >= 0)
			{
				(*fc->getPointer<hb::Vector2d>("direction")).y = -value;
				(*fc->getPointer<hb::Vector2d>("last_direction")) = (*fc->getPointer<hb::Vector2d>("direction"));
				fc->getPointer<hb::SpriteComponent>("player_sprite")->setSprite((*fc->getPointer<hb::Sprite>("sprite_up")));
			}
			else if (code == sf::Keyboard::Key::S and (*fc->getPointer<hb::Vector2d>("direction")).y <= 0)
			{
				(*fc->getPointer<hb::Vector2d>("direction")).y = value;
				(*fc->getPointer<hb::Vector2d>("last_direction")) = (*fc->getPointer<hb::Vector2d>("direction"));
				fc->getPointer<hb::SpriteComponent>("player_sprite")->setSprite(*fc->getPointer<hb::Sprite>("sprite_down"));
			}
			else if (code == sf::Keyboard::Key::A and (*fc->getPointer<hb::Vector2d>("direction")).x >= 0)
			{
				(*fc->getPointer<hb::Vector2d>("direction")).x = -value;
				(*fc->getPointer<hb::Vector2d>("last_direction")) = (*fc->getPointer<hb::Vector2d>("direction"));
				fc->getPointer<hb::SpriteComponent>("player_sprite")->setSprite(*fc->getPointer<hb::Sprite>("sprite_left"));
			}
			else if (code == sf::Keyboard::Key::D and (*fc->getPointer<hb::Vector2d>("direction")).x <= 0)
			{
				(*fc->getPointer<hb::Vector2d>("direction")).x = value;
				(*fc->getPointer<hb::Vector2d>("last_direction")) = (*fc->getPointer<hb::Vector2d>("direction"));
				fc->getPointer<hb::SpriteComponent>("player_sprite")->setSprite(*fc->getPointer<hb::Sprite>("sprite_right"));
			}
			else if (code == sf::Keyboard::Key::Space)
			{
				//hb::GameObject* bullet = new hb::GameObject({new Bullet(window_manager1, (*getGameObject()->getPointer<hb::Vector2d>("last_direction")))});
				//bullet->setPosition(getGameObject()->getPosition());
			}

			if (event.shift)
				fc->setBool("running", true);
			else
				fc->setBool("running", false);
		});
		auto keyreleased_listener_id = hb::InputManager::instance()->listen(
		[fc](const hb::KeyReleased& event)
		{
			sf::Keyboard::Key code = event.code;
			if (code == sf::Keyboard::Key::W and (*fc->getPointer<hb::Vector2d>("direction")).y < 0)
				(*fc->getPointer<hb::Vector2d>("direction")).y = 0;
			else if (code == sf::Keyboard::Key::S and (*fc->getPointer<hb::Vector2d>("direction")).y > 0)
				(*fc->getPointer<hb::Vector2d>("direction")).y = 0;
			else if (code == sf::Keyboard::Key::A and (*fc->getPointer<hb::Vector2d>("direction")).x < 0)
				(*fc->getPointer<hb::Vector2d>("direction")).x = 0;
			else if (code == sf::Keyboard::Key::D and (*fc->getPointer<hb::Vector2d>("direction")).x > 0)
				(*fc->getPointer<hb::Vector2d>("direction")).x = 0;
			if ((*fc->getPointer<hb::Vector2d>("direction")) != hb::Vector2d())
				(*fc->getPointer<hb::Vector2d>("last_direction")) = (*fc->getPointer<hb::Vector2d>("direction"));

		});
		auto mousebuttonworld_listener_id = hb::InputManager::instance()->listen([fc](const hb::MouseButtonWorld& e)
		{
			fc->getGameObject()->setPosition(hb::Vector3d(e.x, e.y, fc->getGameObject()->getPosition().z));
		});

		fc->setPointer("keypressed_listener_id", keypressed_listener_id);
		fc->setPointer("keyreleased_listener_id", keyreleased_listener_id);
		fc->setPointer("mousebuttonworld_listener_id", mousebuttonworld_listener_id);
	});

	// define update function
	fc->setUpdateFunction([fc] ()
	{
		if ((*fc->getPointer<hb::Vector2d>("direction")) == hb::Vector2d(0,0))
			fc->getPointer<hb::SpriteComponent>("player_sprite")->stop();
		else
			fc->getPointer<hb::SpriteComponent>("player_sprite")->play();

		hb::CollisionComponent* m_collision = fc->getPointer<hb::CollisionComponent>("m_collision");

		while(!m_collision->empty())
		{
			hb::CollisionComponent::Collision c = m_collision->nextCollision();
			if (c.object->getComponent<hb::FunctionComponent>()->getBool("is_wall"))
			{
				fc->getGameObject()->setPosition(*fc->getPointer<hb::Vector3d>("last_position"));
			}
		}
		hb::Vector3d p = fc->getGameObject()->getPosition();
		fc->setPointer("last_position", new hb::Vector3d(p));
		bool running = fc->getBool("running");
		fc->getGameObject()->setPosition((p + (*fc->getPointer<hb::Vector2d>("direction")).normalized() * 100 * (running? 2:1) * hb::Time::deltaTime.asSeconds()));

	});

	//define destructor function
	fc->setDestroyFunction([fc] ()
	{
		hb::InputManager::instance()->ignore(fc->getPointer<hb::InputManager::ListenerId<hb::KeyPressed>>("keypressed_listener_id"));
		hb::InputManager::instance()->ignore(fc->getPointer<hb::InputManager::ListenerId<hb::KeyReleased>>("keyreleased_listener_id"));
		hb::InputManager::instance()->ignore(fc->getPointer<hb::InputManager::ListenerId<hb::MouseButtonWorld>>("mousebuttonworld_listener_id"));
	});

	return player;
}