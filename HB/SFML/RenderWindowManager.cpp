#include "RenderWindowManager.h"
using namespace hb;


RenderWindowManager::RenderWindowManager()
{}


RenderWindowManager::RenderWindowManager(sf::RenderWindow* window):
m_window(window)
{}


RenderWindowManager::~RenderWindowManager()
{
	delete m_window;
}


void RenderWindowManager::setWindow(sf::RenderWindow* window)
{
	m_window = window;
}


sf::RenderWindow* RenderWindowManager::getWindow()
{
	return m_window;
}


const sf::RenderWindow* RenderWindowManager::getWindow() const
{
	return m_window;
}


void RenderWindowManager::addDrawable(std::pair<double, sf::Sprite> drawable)
{
	m_drawables.push(drawable);
}


void RenderWindowManager::draw()
{
	m_window->clear();
	while (not m_drawables.empty())
	{
		sf::Sprite d = m_drawables.top().second;
		m_drawables.pop();
		m_window->draw(d);
	}
	m_window->display();
}
