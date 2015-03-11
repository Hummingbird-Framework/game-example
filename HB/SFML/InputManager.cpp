#include "InputManager.h"
using namespace hb;

std::unique_ptr<InputManager> InputManager::s_instance = nullptr;

InputManager* InputManager::instance()
{
	if (s_instance == nullptr)
		s_instance = std::unique_ptr<InputManager>(new InputManager());
	return s_instance.get();
}


void InputManager::update()
{
	sf::Event event;
	while (window_manager1.getWindow()->pollEvent(event))
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
			if (not sf::Keyboard::isKeyPressed(event.key.code))
			{
				hb::KeyPressed kp(event.key);
				hb::InputManager::instance()->message(kp);
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			hb::KeyReleased kr(event.key);
			hb::InputManager::instance()->message(kr);
		}
		else if (event.type == sf::Event::JoystickButtonPressed)
		{
			if (not sf::Joystick::isButtonPressed(event.joystickButton.joystickId, event.joystickButton.button))
			{
				hb::JoyButtonPressed jbp(event.joystickButton);
				hb::InputManager::instance()->message(jbp);
			}
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
}