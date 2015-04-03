#include <Box2D/Box2D.h>
#include "HB/Core.h"
#include "HB/SFML.h"

class B2dDebugDraw : public b2Draw
{
public:
	std::vector<sf::ConvexShape*> shapes;
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::ConvexShape* shape = new sf::ConvexShape;
		shape->setPointCount(vertexCount);
		hb::Vector3d p;
		for (int i = 0; i < vertexCount; ++i)
		{
			p = hb::Renderer::getCamera().ObjectspaceToDrawspace(hb::Vector3d(vertices[i].x, vertices[i].y, 0));
			shape->setPoint(i, sf::Vector2f(p.x, p.y));
		}
		shape->setOutlineThickness(1);
		shape->setOutlineColor(sf::Color(0, 255, 0));
		shape->setFillColor(sf::Color(0,0,0,0));
		shapes.push_back(shape);
		hb::Renderer::addDrawable(std::pair<hb::Vector3d, sf::Drawable*>(hb::Vector3d(0,0,1000), shape));
	}
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
	{
		sf::ConvexShape* shape = new sf::ConvexShape;
		shape->setPointCount(vertexCount);
		hb::Vector3d p;
		for (int i = 0; i < vertexCount; ++i)
		{
			p = hb::Renderer::getCamera().ObjectspaceToDrawspace(hb::Vector3d(vertices[i].x, vertices[i].y, 0));
			shape->setPoint(i, sf::Vector2f(p.x, p.y));
		}
		shape->setOutlineThickness(1);
		shape->setOutlineColor(sf::Color(0, 255, 0));
		shape->setFillColor(sf::Color(0,0,0,0));
		shapes.push_back(shape);
		hb::Renderer::addDrawable(std::pair<hb::Vector3d, sf::Drawable*>(hb::Vector3d(0,0,1000), shape));
	}
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {hb_log("DrawCircle");}
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {hb_log("DrawSolidCircle");}
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {hb_log("DrawSegment");}
	void DrawTransform(const b2Transform& xf) {hb_log("DrawTransform");}
};