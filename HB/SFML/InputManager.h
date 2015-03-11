#ifndef HB_INPUT_MANAGER_H
#define HB_INPUT_MANAGER_H
#include <memory>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Base/EventManager.h"
#include "Renderer.h"

// WISHLIST: Gestionar el input de manera que se de solo una vez el evento de pressed y released y que se le pueda preguntar por el estado de las teclas.

namespace hb
{

	typedef sf::Keyboard Keyboard;
	typedef sf::Joystick Joystick;
	typedef sf::Mouse Mouse;

	struct MouseButtonWindow
	{
		Mouse::Button button;
		int x, y;
		explicit MouseButtonWindow(const sf::Event::MouseButtonEvent& ev):
		button(ev.button),
		x(ev.x),
		y(ev.y)
		{}
	};

	struct MouseButtonWorld
	{
		Mouse::Button button;
		int x, y;
		explicit MouseButtonWorld(const sf::Event::MouseButtonEvent& ev):
		button(ev.button),
		x(ev.x),
		y(ev.y)
		{
			x += Renderer::getWindow().getView().getCenter().x - Renderer::getWindow().getSize().x / 2;
			y += Renderer::getWindow().getView().getCenter().y - Renderer::getWindow().getSize().y / 2;
		}
	};

	struct KeyPressed
	{
		Keyboard::Key code;
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
		Keyboard::Key code;
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

		void update();

	private:
		static std::unique_ptr<InputManager> s_instance;
	};
}
#endif