#ifndef HB_INPUT_MANAGER_H
#define HB_INPUT_MANAGER_H
#include <memory>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Base/EventManager.h"
#include "RenderWindowManager.h"

// WISHLIST: Gestionar el input de manera que se de solo una vez el evento de pressed y released y que se le pueda preguntar por el estado de las teclas.

namespace hb
{
	struct MouseButtonWindow
	{
		sf::Mouse::Button button;
		int x, y;
		explicit MouseButtonWindow(const sf::Event::MouseButtonEvent& ev):
		button(ev.button),
		x(ev.x),
		y(ev.y)
		{}
	};

	struct MouseButtonWorld
	{
		sf::Mouse::Button button;
		int x, y;
		explicit MouseButtonWorld(const sf::Event::MouseButtonEvent& ev, const hb::RenderWindowManager& window):
		button(ev.button),
		x(ev.x),
		y(ev.y)
		{
			x += window.getWindow()->getView().getCenter().x - window.getWindow()->getSize().x / 2;
			y += window.getWindow()->getView().getCenter().y - window.getWindow()->getSize().y / 2;
		}
	};

	struct KeyPressed
	{
		sf::Keyboard::Key code;
		bool alt, control, shift, system;
		explicit KeyPressed(const sf::Event::KeyEvent& ev):
		code(ev.code),
		alt(ev.alt),
		control(ev.control),
		shift(ev.shift),
		system(ev.system)
		{}
	};

	struct KeyReleased
	{
		sf::Keyboard::Key code;
		bool alt, control, shift, system;
		explicit KeyReleased(const sf::Event::KeyEvent& ev):
		code(ev.code),
		alt(ev.alt),
		control(ev.control),
		shift(ev.shift),
		system(ev.system)
		{}
	};


	struct JoyButtonPressed
	{
		unsigned int joystickId, button;
		explicit JoyButtonPressed(const sf::Event::JoystickButtonEvent& ev):
		joystickId(ev.joystickId),
		button(ev.button)
		{}
	};


	struct JoyButtonReleased
	{
		unsigned int joystickId, button;
		explicit JoyButtonReleased(const sf::Event::JoystickButtonEvent& ev):
		joystickId(ev.joystickId),
		button(ev.button)
		{}
	};


	struct JoyAxis
	{
		unsigned int joystickId;
		sf::Joystick::Axis axis;
		float position;
		explicit JoyAxis(const sf::Event::JoystickMoveEvent& ev):
		joystickId(ev.joystickId),
		axis(ev.axis),
		position(ev.position)
		{}
	};


	class InputManager : public hb::EventManager<MouseButtonWindow, MouseButtonWorld, KeyPressed, KeyReleased, JoyButtonPressed, JoyButtonReleased, JoyAxis>
	{
	public:
		static InputManager* instance();

	private:
		static std::unique_ptr<InputManager> s_instance;
	};
}
#endif