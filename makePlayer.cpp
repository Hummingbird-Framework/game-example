#include "makeObjects.h"

hb::GameObject* makePlayer()
{
	// Define the player GameObject
	auto player = new hb::GameObject
	{
		new hb::SpriteComponent(),
		new hb::CollisionComponent(hb::Vector2d(32, 32)),
		new hb::FunctionComponent(),
		new hb::ListenerComponent()
	};

	// Set name
	player->setName("Player");

	// get the FunctionComponent we added in the definition
	auto fc = player->getComponent<hb::FunctionComponent>();

	// run initialization code (define variables and event callbacks)
	player->setPosition(hb::Vector3d(150, 150, 0));
	struct Data
	{
		hb::Vector2d direction; //new hb::Vector2d());
		hb::Vector2d last_direction; //new hb::Vector2d(0, -1));
		bool running; //false);
		hb::SpriteComponent* player_sprite; //player->getComponent<hb::SpriteComponent>());
		hb::CollisionComponent* m_collision; //player->getComponent<hb::CollisionComponent>());
		hb::Vector3d last_position; //new hb::Vector3d(player->getPosition()));
		hb::Sprite sprite_down;
		hb::Sprite sprite_left;
		hb::Sprite sprite_right;
		hb::Sprite sprite_up;
	};
	Data* data = new Data;

	data->direction      = hb::Vector2d();
	data->last_direction = hb::Vector2d(0, -1);
	data->running        = false;
	data->player_sprite  = player->getComponent<hb::SpriteComponent>();
	data->m_collision    = player->getComponent<hb::CollisionComponent>();
	data->last_position  = hb::Vector3d(player->getPosition());

	player->getComponent<hb::CollisionComponent>()->setPosition(hb::Vector3d(-16, -16, 0));

	hb::Texture tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
	hb::Sprite sprite_down = hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d(), {0, 1, 2, 1}, hb::Time::seconds(0.3));
	sprite_down.setCenter(hb::Vector2d(16, 16));
	data->sprite_down = sprite_down;
	tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
	hb::Sprite sprite_left = hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d(), {3, 4, 5, 4}, hb::Time::seconds(0.3));
	sprite_left.setCenter(hb::Vector2d(16, 16));
	data->sprite_left = sprite_left;
	tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
	hb::Sprite sprite_right = hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d(), {6, 7, 8, 7}, hb::Time::seconds(0.3));
	sprite_right.setCenter(hb::Vector2d(16, 16));
	data->sprite_right = sprite_right;
	tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
	hb::Sprite sprite_up = hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d(), {9, 10, 11, 10}, hb::Time::seconds(0.3));
	sprite_up.setCenter(hb::Vector2d(16, 16));
	data->sprite_up = sprite_up;

	data->player_sprite->setSprite(data->sprite_down);

	// define update function
	fc->setUpdateFunction([=] ()
	{
		if (data->direction == hb::Vector2d(0,0))
			data->player_sprite->stop();
		else
			data->player_sprite->play();

		hb::CollisionComponent* m_collision = data->m_collision;

		while(!m_collision->empty())
		{
			hb::CollisionComponent::Collision c = m_collision->nextCollision();
			if (c.object->getName() == "Wall")
			{
				player->setPosition(data->last_position);
			}
		}
		hb::Vector3d p = player->getPosition();
		data->last_position = hb::Vector3d(p);
		bool running = data->running;
		//hb::Vector3d dir = hb::Vector3d(fc->getPointer<hb::Vector2d>("direction")->x, 0, fc->getPointer<hb::Vector2d>("direction")->y);
		hb::Vector3d dir = hb::Vector3d(data->direction.x, data->direction.y, 0);
		player->setPosition(p + (dir.normalized() * 100 * (running? 2:1) * hb::Time::deltaTime.asSeconds()));

		hb::Renderer::getCamera().setPosition(player->getPosition());
	});

	// Define input listeners
	hb::InputManager::ListenerId<hb::KeyPressed> keypressed_listener_id = hb::InputManager::ListenerId<hb::KeyPressed>();
	hb::InputManager::ListenerId<hb::KeyReleased> keyreleased_listener_id = hb::InputManager::ListenerId<hb::KeyReleased>();
	keypressed_listener_id = hb::InputManager::instance()->listen(
	[=](const hb::KeyPressed& event)
	{
		int value = 1;

		hb::Keyboard::Key code = event.code;
		if (code == hb::Keyboard::Key::W and data->direction.y >= 0)
		{
			player->getComponent<hb::ListenerComponent>()->setDirection(hb::Vector3d(0, -1, 0));
			data->direction.y = -value;
			data->last_direction = data->direction;
			data->player_sprite->setSprite(data->sprite_up);
		}
		else if (code == hb::Keyboard::Key::S and data->direction.y <= 0)
		{
			player->getComponent<hb::ListenerComponent>()->setDirection(hb::Vector3d(0, 1, 0));
			data->direction.y = value;
			data->last_direction = data->direction;
			data->player_sprite->setSprite(data->sprite_down);
		}
		else if (code == hb::Keyboard::Key::A and data->direction.x >= 0)
		{
			player->getComponent<hb::ListenerComponent>()->setDirection(hb::Vector3d(-1, 0, 0));
			data->direction.x = -value;
			data->last_direction = data->direction;
			data->player_sprite->setSprite(data->sprite_left);
		}
		else if (code == hb::Keyboard::Key::D and data->direction.x <= 0)
		{
			player->getComponent<hb::ListenerComponent>()->setDirection(hb::Vector3d(1, 0, 0));
			data->direction.x = value;
			data->last_direction = data->direction;
			data->player_sprite->setSprite(data->sprite_right);
		}
		else if (code == hb::Keyboard::Key::Space)
		{
			auto bullet = makeBullet(hb::Vector2d(data->last_direction.x, data->last_direction.y));
			bullet->setPosition(player->getPosition());
		}
		else if (code == hb::Keyboard::Key::LShift)
		{
			data->running = true;
		}
	});
	keyreleased_listener_id = hb::InputManager::instance()->listen(
	[=](const hb::KeyReleased& event)
	{
		hb::Keyboard::Key code = event.code;
		if (code == hb::Keyboard::Key::W and data->direction.y < 0)
			data->direction.y = 0;
		else if (code == hb::Keyboard::Key::S and data->direction.y > 0)
			data->direction.y = 0;
		else if (code == hb::Keyboard::Key::A and data->direction.x < 0)
			data->direction.x = 0;
		else if (code == hb::Keyboard::Key::D and data->direction.x > 0)
			data->direction.x = 0;
		else if (code == hb::Keyboard::Key::LShift)
			data->running = false;

		if (data->direction != hb::Vector2d())
			data->last_direction = data->direction;


	});
	hb::InputManager::ListenerId<hb::MouseButtonWorld> mousebuttonworld_listener_id = hb::InputManager::ListenerId<hb::MouseButtonWorld>();
	mousebuttonworld_listener_id = hb::InputManager::instance()->listen([=](const hb::MouseButtonWorld& e)
	{
		//player->setPosition(hb::Vector3d(e.x, e.y, player->getPosition().z));
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