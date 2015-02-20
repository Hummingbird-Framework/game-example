#include <iostream>
#include "HB/Base.h"
#include "HB/SFML.h"

class Player : public hb::GameObject::Component
{
public:
	Player(hb::RenderWindowManager* window_manager1):direction(hb::Vector2d()), speed(30), running(false)
	{
		keypressed_listener_id = hb::InputManager::instance()->listen(
		[this](const hb::KeyPressed& event)
		{
			int value = 1;

			sf::Keyboard::Key code = event.code;
			if (code == sf::Keyboard::Key::W and direction.y >= 0)
			{
				direction.y = -value;
				player_sprite->setAnimation(*animation_up);
			}
			else if (code == sf::Keyboard::Key::S and direction.y <= 0)
			{
				direction.y = value;
				player_sprite->setAnimation(*animation_down);
			}
			else if (code == sf::Keyboard::Key::A and direction.x >= 0)
			{
				direction.x = -value;
				player_sprite->setAnimation(*animation_left);
			}
			else if (code == sf::Keyboard::Key::D and direction.x <= 0)
			{
				direction.x = value;
				player_sprite->setAnimation(*animation_right);
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
		});
		mousebuttonworld_listener_id = hb::InputManager::instance()->listen([this](const hb::MouseButtonWorld& e)
		{
			getGameObject()->setPosition(hb::Vector3d(e.x, e.y, getGameObject()->getPosition().z));
		});

		animation_down = new hb::SpriteComponent::Animation("res/drawable/walking-tiles.png", sf::IntRect(96, 128, 96, 128), hb::Vector2d(32, 32), hb::Vector2d(), 0, 2, hb::Time::seconds(0.3));
		animation_left = new hb::SpriteComponent::Animation("res/drawable/walking-tiles.png", sf::IntRect(96, 128, 96, 128), hb::Vector2d(32, 32), hb::Vector2d(), 3, 5, hb::Time::seconds(0.3));
		animation_right = new hb::SpriteComponent::Animation("res/drawable/walking-tiles.png", sf::IntRect(96, 128, 96, 128), hb::Vector2d(32, 32), hb::Vector2d(), 6, 8, hb::Time::seconds(0.3));
		animation_up = new hb::SpriteComponent::Animation("res/drawable/walking-tiles.png", sf::IntRect(96, 128, 96, 128), hb::Vector2d(32, 32), hb::Vector2d(), 9, 11, hb::Time::seconds(0.3));

		this->window_manager1 = window_manager1;
	}

	~Player()
	{
		hb::InputManager::instance()->ignore(keypressed_listener_id);
		hb::InputManager::instance()->ignore(keyreleased_listener_id);
		hb::InputManager::instance()->ignore(mousebuttonworld_listener_id);

		delete animation_up;
		delete animation_down;
		delete animation_left;
		delete animation_right;
	}
	
	hb::Vector2d direction;
	double speed;
	bool running;

	void init() override
	{
		getGameObject()->setPosition(hb::Vector3d(100, 100, 0));
		getGameObject()->addComponent(new hb::SpriteComponent(window_manager1, *animation_down));

		player_sprite = getGameObject()->getComponents<hb::SpriteComponent>()[0];
		player_sprite->stop();
	}

	void update() override
	{
		if (direction == hb::Vector2d(0,0))
			player_sprite->stop();
		else
			player_sprite->play();


		hb::Vector3d p = getGameObject()->getPosition();
		getGameObject()->setPosition((p + direction.normalized() * speed * (running? 2:1) * hb::Time::deltaTime.asSeconds()));
	}

private:
	hb::InputManager::ListenerId<hb::KeyPressed> keypressed_listener_id;
	hb::InputManager::ListenerId<hb::KeyReleased> keyreleased_listener_id;
	hb::InputManager::ListenerId<hb::MouseButtonWorld> mousebuttonworld_listener_id;

	hb::SpriteComponent::Animation* animation_up;
	hb::SpriteComponent::Animation* animation_down;
	hb::SpriteComponent::Animation* animation_left;
	hb::SpriteComponent::Animation* animation_right;

	hb::SpriteComponent* player_sprite;

	hb::RenderWindowManager* window_manager1;
};

int main(int argc, char const *argv[])
{
	hb::RenderWindowManager window_manager1(new sf::RenderWindow(sf::VideoMode(1280, 720), "Game"));
	hb::GameObject* player = new hb::GameObject;
	player->addComponent(new Player(&window_manager1));

	sf::Clock clk;
	hb::Time lastTime = hb::Time::microseconds(clk.getElapsedTime().asMicroseconds());
	while(window_manager1.getWindow()->isOpen())
	{
		hb::Time::deltaTime = hb::Time::microseconds(clk.getElapsedTime().asMicroseconds())-lastTime;
		lastTime = hb::Time::microseconds(clk.getElapsedTime().asMicroseconds());
		
		sf::Event event;
		if (window_manager1.getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window_manager1.getWindow()->close();
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				hb::MouseButtonWorld mbw(event.mouseButton, window_manager1);
				hb::InputManager::instance()->message(mbw);
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				hb::KeyPressed kp(event.key);
				hb::InputManager::instance()->message(kp);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				hb::KeyReleased kr(event.key);
				hb::InputManager::instance()->message(kr);
			}
			else if (event.type == sf::Event::JoystickButtonPressed)
			{
				hb::JoyButtonPressed jbp(event.joystickButton);
				hb::InputManager::instance()->message(jbp);
			}
			else if (event.type == sf::Event::JoystickButtonReleased)
			{
				hb::JoyButtonReleased jbr(event.joystickButton);
				hb::InputManager::instance()->message(jbr);
			}
			else if (event.type == sf::Event::JoystickMoved)
			{
				hb::JoyAxis ja(event.joystickMove);
				hb::InputManager::instance()->message(ja);
			}
			else if (event.type == sf::Event::Resized)
			{
				auto view = window_manager1.getWindow()->getView();
				view.setSize(sf::Vector2f(event.size.width, event.size.height));
				window_manager1.getWindow()->setView(view);
			}
		}

		hb::GameObject::updateAll();
		window_manager1.draw();
	}
	hb::GameObject::destroyAll();
}