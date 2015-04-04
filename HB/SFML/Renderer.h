#ifndef HB_RENDER_WINDOW_MANAGER_H
#define HB_RENDER_WINDOW_MANAGER_H
#include <string>
#include <memory>
#include <queue>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Core/Color.h"
#include "../Core/Vector2d.h"
#include "../Core/Vector3d.h"
#include "Camera.h"

namespace hb
{
	/**
	 * \addtogroup SFML
	 * @{
	 */
	typedef sf::RenderWindow Window;

	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		static void createWindow(const Vector2d& size, std::string title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
		static void setCamera(const Camera& camera);
		static Camera& getCamera();
		static Window& getWindow();
		static void addDrawable(std::pair<Vector3d, sf::Drawable*> drawable);
		static void draw();
		static void setClearColor(const Color& color);

	private:
		class Comparison
		{
		public:
			Comparison(){}
			bool operator() (const std::pair<Vector3d, sf::Drawable*>& lhs, const std::pair<Vector3d, sf::Drawable*>& rhs) const
			{
				return (lhs.first.z > rhs.first.z);
			}
		};
		static std::unique_ptr<Window> s_window;
		static Camera s_camera;
		static sf::Color s_clear_color;
		static std::priority_queue<std::pair<Vector3d, sf::Drawable*>, std::vector<std::pair<Vector3d, sf::Drawable*>>, Comparison> s_drawables;
	};

	//! @}
}
#endif