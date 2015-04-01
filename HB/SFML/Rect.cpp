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


Rect::~Rect()
{};