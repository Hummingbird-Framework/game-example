#include <iostream>
#include "HB/Base.h"
#include "HB/SFML.h"
#include "makeObjects.h"

int main(int argc, char const *argv[])
{
	hb::RenderWindowManager window_manager1(new sf::RenderWindow(sf::VideoMode(1280, 720), "Game"));
	makePlayer(&window_manager1);
	makeWall(&window_manager1, hb::Vector2d(10, 40), hb::Vector2d(10, 100));
	makeWall(&window_manager1, hb::Vector2d(20, 140), hb::Vector2d(100, 10));
	hb::Clock clk;
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

		//std::cout << player->getPosition().x << ", " << player->getPosition().y << std::endl;
		hb::GameObject::updateAll();
		window_manager1.draw();
	}
	hb::GameObject::destroyAll();
}