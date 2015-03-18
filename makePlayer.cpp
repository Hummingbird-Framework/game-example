#include "makeObjects.h"
#include <iostream>

hb::GameObject* makePlayer()
{
	// Define the player GameObject
	auto player = new hb::GameObject
	{
		new hb::SpriteComponent(),
		new hb::CollisionComponent(hb::Vector2d(1, 1)),
		new hb::FunctionComponent()
	};

	// Set name
	player->setName("Player");

	// get the FunctionComponent we added in the definition
	auto fc = player->getComponent<hb::FunctionComponent>();

	// run initialization code (define variables and event callbacks)
	player->setPosition(hb::Vector3d(150/32., 150/32., 0));
	struct Data
	{
		hb::Vector2d direction; //new hb::Vector2d());
		hb::Vector2d last_direction; //new hb::Vector2d(0, -1));
		bool running; //false);
		hb::SpriteComponent* player_sprite; //player->getComponent<hb::SpriteComponent>());
		hb::CollisionComponent* m_collision; //player->getComponent<hb::CollisionComponent>());
		hb::Vector3d last_position; //new hb::Vector3d(player->getPosition()));
		bool is_grounded = false;
	};
	Data* data = new Data;

	data->direction      = hb::Vector2d();
	data->last_direction = hb::Vector2d(1, 0);
	data->player_sprite  = player->getComponent<hb::SpriteComponent>();
	data->m_collision    = player->getComponent<hb::CollisionComponent>();
	data->last_position  = hb::Vector3d(player->getPosition());

	hb::Texture tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
	hb::Sprite sprite = hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d());
	//sprite.setCenter(hb::Vector2d(16, 16));

	data->player_sprite->setSprite(sprite);
	data->player_sprite->setFrameOrder({6, 7, 8, 7});
	data->player_sprite->setFrameTime(hb::Time::seconds(0.1));

	// define update function
	fc->setUpdateFunction([=] ()
	{
		if (data->direction.y > 10.)
			data->direction.y = 10.;

		if (data->direction.x == 0)
			data->player_sprite->stop();
		else
			data->player_sprite->play();

		hb::CollisionComponent* m_collision = data->m_collision;
		bool still_grounded = false;
		while(!m_collision->empty())
		{
			hb::CollisionComponent::Collision c = m_collision->nextCollision();
			if (c.object->getName() == "Wall")
			{
				hb::Vector3d p = player->getPosition();
				if (c.intersection.width < c.intersection.height)
				{
					p.x = data->last_position.x;
				}
				else
				{
					if (c.intersection.top > player->getPosition().y + 0.5)
					{
						still_grounded = true;
					}
					else if (c.intersection.top < player->getPosition().y + 0.5)
					{
						data->direction.y = 0;
					}
					p.y = data->last_position.y;
				}
				player->setPosition(p);
			}
		}
		data->is_grounded = still_grounded;
		if (not data->is_grounded)
		{
			data->direction.y += 9.8 * hb::Time::deltaTime.asSeconds();
		}
		else
		{
			data->direction.y += 0;
		}
		hb::Vector3d p = player->getPosition();
		data->last_position = p;
		//hb::Vector3d dir = hb::Vector3d(fc->getPointer<hb::Vector2d>("direction")->x, 0, fc->getPointer<hb::Vector2d>("direction")->y);
		hb::Vector3d dir = hb::Vector3d(data->direction.x * hb::Time::deltaTime.asSeconds(), data->direction.y * hb::Time::deltaTime.asSeconds(), 0);
		player->setPosition(p + dir);

		hb::Renderer::getCamera().setPosition(player->getPosition());
	});

	// Define input listeners
	hb::InputManager::ListenerId<hb::KeyPressed> keypressed_listener_id = hb::InputManager::ListenerId<hb::KeyPressed>();
	hb::InputManager::ListenerId<hb::KeyReleased> keyreleased_listener_id = hb::InputManager::ListenerId<hb::KeyReleased>();
	keypressed_listener_id = hb::InputManager::instance()->listen(
	[=](const hb::KeyPressed& event)
	{
		int value = 200./32.;

		hb::Keyboard::Key code = event.code;
		if (code == hb::Keyboard::Key::W and data->direction.y >= 0)
		{
			if (data->is_grounded)
				data->direction.y = -5;
		}
		else if (code == hb::Keyboard::Key::A and data->direction.x >= 0)
		{
			data->direction.x = -value;
			data->last_direction = data->direction;
			data->player_sprite->setFrameOrder({3, 4, 5, 4});
		}
		else if (code == hb::Keyboard::Key::D and data->direction.x <= 0)
		{
			data->direction.x = value;
			data->last_direction = data->direction;
			data->player_sprite->setFrameOrder({6, 7, 8, 7});
		}
		else if (code == hb::Keyboard::Key::Space)
		{
			auto bullet = makeBullet(hb::Vector2d(data->last_direction.x, 0));
			if (data->last_direction.x < 0)
				bullet->setPosition(player->getPosition() + hb::Vector3d(0,0.25,0));
			else
				bullet->setPosition(player->getPosition() + hb::Vector3d(0.5,0.25,0));
		}
	});
	keyreleased_listener_id = hb::InputManager::instance()->listen(
	[=](const hb::KeyReleased& event)
	{
		hb::Keyboard::Key code = event.code;
		if (code == hb::Keyboard::Key::A and data->direction.x < 0)
			data->direction.x = 0;
		else if (code == hb::Keyboard::Key::D and data->direction.x > 0)
			data->direction.x = 0;
	});
	hb::InputManager::ListenerId<hb::MouseButtonWorld> mousebuttonworld_listener_id = hb::InputManager::ListenerId<hb::MouseButtonWorld>();
	mousebuttonworld_listener_id = hb::InputManager::instance()->listen([=](const hb::MouseButtonWorld& e)
	{
		makeWall(hb::Vector2d(e.x, e.y), hb::Vector2d(1, 1));
		std::cout << "wall: " << e.x << ", " << e.y << std::endl;
		std::cout << "player: " << player->getPosition().x << ", " << player->getPosition().y << std::endl;
	});

	//define destructor function
	fc->setDestroyFunction([=] ()
	{
		delete data;
		hb::InputManager::instance()->ignore(keypressed_listener_id);
		hb::InputManager::instance()->ignore(keyreleased_listener_id);
		hb::InputManager::instance()->ignore(mousebuttonworld_listener_id);
	});

	return player;
}