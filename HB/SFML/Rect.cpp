#include "Rect.h"
using namespace hb;
Rect::Rect():
sf::Rect<double>()
{}


Rect::Rect(double rectLeft, double rectTop, double rectWidth, double rectHeight):
sf::Rect<double>(rectLeft, rectTop, rectWidth, rectHeight)
{}


Rect::Rect(const Vector2d &position, const Vector2d &size):
sf::Rect<double>(sf::Vector2<double>(position.x, position.y), sf::Vector2<double>(size.x, size.y))
{}


Rect::Rect(const std::string& str):
sf::Rect<double>()
{
	std::regex re ("\\(\\s*([0-9]+(?:\\.[0-9]+)?)\\s*,\\s*([0-9]+(?:\\.[0-9]+)?)\\s*,\\s*([0-9]+(?:\\.[0-9]+)?)\\s*,\\s*([0-9]+(?:\\.[0-9]+)?)\\s*\\)");
	std::smatch sm;
	std::regex_match (str, sm, re);
	if (not sm.empty())
	{
		left   = strtod(sm.str(1).c_str(), NULL);
		top    = strtod(sm.str(2).c_str(), NULL);
		width  = strtod(sm.str(3).c_str(), NULL);
		height = strtod(sm.str(4).c_str(), NULL);
	}
}


Rect::~Rect()
{};