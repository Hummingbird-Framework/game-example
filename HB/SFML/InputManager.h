#ifndef HB_INPUT_MANAGER_H
#define HB_INPUT_MANAGER_H
#include <memory>
#include <map>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Core/MessageManager.h"
#include "../Core/Game.h"
#include "Renderer.h"

namespace hb
{
	/**
	 * \addtogroup SFML
	 * @{
	 */
	typedef sf::Keyboard Keyboard;
	typedef sf::Joystick Joystick;
	typedef sf::Mouse Mouse;
	typedef sf::Event Event;

	struct MouseButtonWindow
	{
		Mouse::Button button;
		int x, y;
		explicit MouseButtonWindow(const Event::MouseButtonEvent& ev):
		button(ev.button),
		x(ev.x),
		y(ev.y)
		{}
	};

	struct MouseButtonWorld
	{
		Mouse::Button button;
		double x, y;
		explicit MouseButtonWorld(const Event::MouseButtonEvent& ev):
		button(ev.button),
		x(ev.x),
		y(ev.y)
		{
			x += Renderer::getWindow().getView().getCenter().x - Renderer::getWindow().getSize().x / 2;
			y += Renderer::getWindow().getView().getCenter().y - Renderer::getWindow().getSize().y / 2;
			Vector3d v = x * Renderer::getCamera().getInverseAxisX() + y * Renderer::getCamera().getInverseAxisY();
			x = v.x;
			y = v.y;
		}
	};

	struct KeyPressed
	{
		Keyboard::Key code;
		bool alt, control, shift, system;
		explicit KeyPressed(const Event::KeyEvent& ev):
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
		explicit KeyReleased(const Event::KeyEvent& ev):
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
		explicit JoyButtonPressed(const Event::JoystickButtonEvent& ev):
		joystickId(ev.joystickId),
		button(ev.button)
		{}
	};


	struct JoyButtonReleased
	{
		unsigned int joystickId, button;
		explicit JoyButtonReleased(const Event::JoystickButtonEvent& ev):
		joystickId(ev.joystickId),
		button(ev.button)
		{}
	};


	struct JoyAxis
	{
		unsigned int joystickId;
		Joystick::Axis axis;
		float position;
		explicit JoyAxis(const Event::JoystickMoveEvent& ev):
		joystickId(ev.joystickId),
		axis(ev.axis),
		position(ev.position)
		{}
	};

	struct WindowResized
	{
		unsigned int width, height;
		explicit WindowResized(const Event::SizeEvent& ev):
		width(ev.width),
		height(ev.height)
		{}
	};

	class InputManager : public hb::MessageManager<MouseButtonWindow, MouseButtonWorld, KeyPressed, KeyReleased, JoyButtonPressed, JoyButtonReleased, JoyAxis, WindowResized>
	{
	public:
		static InputManager* instance();

		void update();

	private:
		static std::unique_ptr<InputManager> s_instance;

		std::map<Keyboard::Key, bool> m_pressed_keys;
		std::map<std::pair<int, int>, bool> m_pressed_buttons;
	};
	//! @}
}
#endif