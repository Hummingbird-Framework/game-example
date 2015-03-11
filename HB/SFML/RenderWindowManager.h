#ifndef HB_RENDER_WINDOW_MANAGER_H
#define HB_RENDER_WINDOW_MANAGER_H
#include <queue>
#include <SFML/Graphics.hpp>
#include "../Base/Transform.h"

namespace hb
{
	typedef sf::RenderWindow Window;

	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		const Window& getWindow();
		const Window& getWindow() const;
		void addDrawable(std::pair<const Transform&, sf::Sprite> drawable);
		void draw();

	private:
		class Comparison
		{
		public:
			Comparison(){}
			bool operator() (const std::pair<double, sf::Sprite>& lhs, const std::pair<double, sf::Sprite>& rhs) const
			{
				return (lhs.first > rhs.first);
			}
		};
		sf::RenderWindow* m_window;
		std::priority_queue<std::pair<double, sf::Sprite>, std::vector<std::pair<double, sf::Sprite>>, Comparison> m_drawables;
	};
}
#endif