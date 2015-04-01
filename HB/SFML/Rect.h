#ifndef HB_RECT_H
#define HB_RECT_H
#include <string>
#include <SFML/Graphics.hpp>
#include "../Core/Vector2d.h"

namespace hb
{
	/**
	 * \class Rect
	 * \ingroup SFML
	 */
	class Rect : public sf::Rect<double>
	{
	public:
		Rect();
		Rect(double rectLeft, double rectTop, double rectWidth, double rectHeight);
		Rect(const std::string& str);
		Rect(const Vector2d &position, const Vector2d &size);
		~Rect();
		
	};
}
#endif