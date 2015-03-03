#include "Player.h"
#include <iostream>

Player::Player(hb::RenderWindowManager* window_manager1):direction(hb::Vector2d()), speed(100), running(false), last_direction(hb::Vector2d(0, -1))
{
	keypressed_listener_id = hb::InputManager::instance()->listen(
	[this](const hb::KeyPressed& event)
	{
		int value = 1;

		sf::Keyboard::Key code = event.code;
		if (code == sf::Keyboard::Key::W and direction.y >= 0)
		{
			direction.y = -value;
			last_direction = direction;
			player_sprite->setSprite(sprite_up);
		}
		else if (code == sf::Keyboard::Key::S and direction.y <= 0)
		{
			direction.y = value;
			last_direction = direction;
			player_sprite->setSprite(sprite_down);
		}
		else if (code == sf::Keyboard::Key::A and direction.x >= 0)
		{
			direction.x = -value;
			last_direction = direction;
			player_sprite->setSprite(sprite_left);
		}
		else if (code == sf::Keyboard::Key::D and direction.x <= 0)
		{
			direction.x = value;
			last_direction = direction;
			player_sprite->setSprite(sprite_right);
		}
		else if (code == sf::Keyboard::Key::Space)
		{
			shoot();
		}

		if (event.shift)
			running = true;
		else
			running = false;
	});
	keyreleased_listener_id = hb::InputManager::instance()->listen(
	[this](const hb::KeyReleased& event)
	{
		sf::Keyboard::Key code = event.code;
		if (code == sf::Keyboard::Key::W and direction.y < 0)
			direction.y = 0;
		else if (code == sf::Keyboard::Key::S and direction.y > 0)
			direction.y = 0;
		else if (code == sf::Keyboard::Key::A and direction.x < 0)
			direction.x = 0;
		else if (code == sf::Keyboard::Key::D and direction.x > 0)
			direction.x = 0;
		if (direction != hb::Vector2d())
			last_direction = direction;

	});
	mousebuttonworld_listener_id = hb::InputManager::instance()->listen([this](const hb::MouseButtonWorld& e)
	{
		getGameObject()->setPosition(hb::Vector3d(e.x, e.y, getGameObject()->getPosition().z));
	});

	hb::Texture tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
	sprite_down = hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d(), 0, 2, hb::Time::seconds(0.3));
	tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
	sprite_left = hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d(), 3, 5, hb::Time::seconds(0.3));
	tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
	sprite_right = hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d(), 6, 8, hb::Time::seconds(0.3));
	tex = hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(96, 128, 96, 128));
	sprite_up = hb::Sprite(tex, hb::Vector2d(32, 32), hb::Vector2d(), 9, 11, hb::Time::seconds(0.3));

	this->window_manager1 = window_manager1;
	m_collision = new hb::CollisionComponent(hb::Vector2d(32, 32));
}

Player::~Player()
{
	hb::InputManager::instance()->ignore(keypressed_listener_id);
	hb::InputManager::instance()->ignore(keyreleased_listener_id);
	hb::InputManager::instance()->ignore(mousebuttonworld_listener_id);
}

hb::Vector2d direction;
double speed;
bool running;

void Player::init()
{
	getGameObject()->setPosition(hb::Vector3d(100, 100, 0));
	last_position = getGameObject()->getPosition();
	getGameObject()->addComponent(new hb::SpriteComponent(window_manager1, sprite_down));
	hb::Texture rec = hb::Texture::makeTexture(hb::Vector2d(32, 32));
	rec.fill(hb::Rect(0,0,31,31), hb::Color(0,0,0,0));
	rec.stroke(hb::Vector2d(0,0), hb::Vector2d(31,0), hb::Color(0, 255, 0));
	rec.stroke(hb::Vector2d(0,0), hb::Vector2d(0,31), hb::Color(0, 255, 0));
	rec.stroke(hb::Vector2d(0,31), hb::Vector2d(31,31), hb::Color(0, 255, 0));
	rec.stroke(hb::Vector2d(31,0), hb::Vector2d(31,31), hb::Color(0, 255, 0));
	getGameObject()->addComponent(new hb::SpriteComponent(window_manager1, hb::Sprite(rec, hb::Vector2d(32, 32))));
	getGameObject()->addComponent(m_collision);

	player_sprite = getGameObject()->getComponent<hb::SpriteComponent>();
	player_sprite->stop();
}

void Player::update()
{
	if (direction == hb::Vector2d(0,0))
		player_sprite->stop();
	else
		player_sprite->play();

	while(!m_collision->empty())
	{
		hb::CollisionComponent::Collision c = m_collision->nextCollision();
		if (c.object->getComponents<Wall>().size() != 0)
		{
			getGameObject()->setPosition(last_position);
		}
	}
	hb::Vector3d p = getGameObject()->getPosition();
	last_position = p;
	getGameObject()->setPosition((p + direction.normalized() * speed * (running? 2:1) * hb::Time::deltaTime.asSeconds()));

}

void Player::shoot()
{
	hb::GameObject* bullet = new hb::GameObject({new Bullet(window_manager1, last_direction)});
	bullet->setPosition(getGameObject()->getPosition());
}
