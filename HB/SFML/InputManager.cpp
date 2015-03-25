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
	Event event;
	while (Renderer::getWindow().pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			Renderer::getWindow().close();
			hb::Game::running(false);
		}
		else if (event.type == Event::MouseButtonPressed)
		{
			hb::MouseButtonWorld mbw(event.mouseButton);
			hb::InputManager::instance()->message(mbw);
			hb::MouseButtonWindow mbwin(event.mouseButton);
			hb::InputManager::instance()->message(mbwin);
		}
		else if (event.type == Event::KeyPressed)
		{
			if (not m_pressed_keys[event.key.code])
			{
				m_pressed_keys[event.key.code] = true;
				hb::KeyPressed kp(event.key);
				hb::InputManager::instance()->message(kp);
			}
		}
		else if (event.type == Event::KeyReleased)
		{
			m_pressed_keys[event.key.code] = false;
			hb::KeyReleased kr(event.key);
			hb::InputManager::instance()->message(kr);
		}
		else if (event.type == Event::JoystickButtonPressed)
		{
			if (not m_pressed_buttons[std::pair<int, int>(event.joystickButton.joystickId, event.joystickButton.button)])
			{
				m_pressed_buttons[std::pair<int, int>(event.joystickButton.joystickId, event.joystickButton.button)] = true;
				hb::JoyButtonPressed jbp(event.joystickButton);
				hb::InputManager::instance()->message(jbp);
			}
		}
		else if (event.type == Event::JoystickButtonReleased)
		{
			m_pressed_buttons[std::pair<int, int>(event.joystickButton.joystickId, event.joystickButton.button)] = false;
			hb::JoyButtonReleased jbr(event.joystickButton);
			hb::InputManager::instance()->message(jbr);
		}
		else if (event.type == Event::JoystickMoved)
		{
			hb::JoyAxis ja(event.joystickMove);
			hb::InputManager::instance()->message(ja);
		}
		else if (event.type == Event::Resized)
		{
			WindowResized wr = WindowResized(event.size);
			InputManager::instance()->message(wr);
		}
	}
}