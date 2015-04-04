#include "Renderer.h"
using namespace hb;


std::unique_ptr<Window> Renderer::s_window;
Camera Renderer::s_camera;
sf::Color Renderer::s_clear_color(0,0,0,255);
std::priority_queue<std::pair<Vector3d, sf::Drawable*>, std::vector<std::pair<Vector3d, sf::Drawable*>>, Renderer::Comparison> Renderer::s_drawables;


Renderer::Renderer()
{

}


Renderer::~Renderer()
{

}


void Renderer::createWindow(const Vector2d& size, std::string title, sf::Uint32 style, const sf::ContextSettings& settings)
{
	s_window = std::unique_ptr<Window>(new Window(sf::VideoMode(size.x, size.y), title, style, settings));
}


void Renderer::setCamera(const Camera& camera)
{
	s_camera = camera;
}


Camera& Renderer::getCamera()
{
	return s_camera;
}


Window& Renderer::getWindow()
{
	return *(s_window.get());
}


void Renderer::addDrawable(std::pair<Vector3d, sf::Drawable*> drawable)
{
	if (drawable.first.z > s_camera.getZNear() and drawable.first.z < s_camera.getZFar())
		s_drawables.push(drawable);
}


void Renderer::draw()
{
	s_window->clear(s_clear_color);
	sf::View view = getWindow().getView();
	hb::Vector3d cam_pos = s_camera.ObjectspaceToDrawspace(s_camera.getPosition());
	view.setCenter(cam_pos.x, cam_pos.y);
	getWindow().setView(view);
	while (not s_drawables.empty())
	{
		sf::Drawable* d = s_drawables.top().second;
		s_drawables.pop();
		s_window->draw(*d);
	}
	s_window->display();
}


void Renderer::setClearColor(const Color& color)
{
	s_clear_color.r = color.r*255;
	s_clear_color.g = color.g*255;
	s_clear_color.b = color.b*255;
	s_clear_color.a = color.a*255;
}
