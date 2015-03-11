#include "Renderer.h"
using namespace hb;


std::unique_ptr<Window> Renderer::m_window;
Camera Renderer::m_camera;
std::priority_queue<std::pair<Vector3d, sf::Drawable*>, std::vector<std::pair<Vector3d, sf::Drawable*>>, Renderer::Comparison> Renderer::m_drawables;


Renderer::Renderer()
{

}


Renderer::~Renderer()
{

}


void Renderer::createWindow(const Vector2d& size, std::string title, sf::Uint32 style, const sf::ContextSettings& settings)
{
	m_window = std::unique_ptr<Window>(new Window(sf::VideoMode(size.x, size.y), title, style, settings));
}


void Renderer::setCamera(const Camera& camera)
{
	m_camera = camera;
}


Camera& Renderer::getCamera()
{
	return m_camera;
}


Window& Renderer::getWindow()
{
	return *(m_window.get());
}


void Renderer::addDrawable(std::pair<Vector3d, sf::Drawable*> drawable)
{
	if (drawable.first.z > m_camera.getZNear() and drawable.first.z < m_camera.getZFar())
		m_drawables.push(drawable);
}


void Renderer::draw()
{
	m_window->clear();
	sf::View view = getWindow().getView();
	view.setCenter(m_camera.getPosition().x, m_camera.getPosition().y);
	getWindow().setView(view);
	while (not m_drawables.empty())
	{
		sf::Drawable* d = m_drawables.top().second;
		m_drawables.pop();
		m_window->draw(*d);
	}
	m_window->display();
}
