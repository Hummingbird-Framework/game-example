#ifndef HB_RECT_H
#define HB_RECT_H
#include <SFML/Graphics.hpp>
#include "../Base/Vector2d.h"

namespace hb
{
	class Rect : public sf::Rect<double>
	{
	public:
		Rect();
		Rect(double rectLeft, double rectTop, double rectWidth, double rectHeight);
		Rect(const Vector2d &position, const Vector2d &size);
		~Rect();
		
	};
}
#endif