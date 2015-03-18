#include "ClickableComponent.h"
using namespace hb;

std::string ClickableComponent::s_footprint = "Clickable";

ClickableComponent::ClickableComponent():
ClickableComponent(hb::Vector2d())
{

}


GameObject::Component* ClickableComponent::factory(std::map<std::string, std::string>& properties, int i)
{
	ClickableComponent* c = new ClickableComponent();
	c->setPosition(hb::Vector3d(properties[s_footprint + "[" + std::to_string(i) + "].position"]));
	c->setSize(hb::Vector2d(properties[s_footprint + "[" + std::to_string(i) + "].size"]));
	return c;
}


const std::string& ClickableComponent::getFootprint()
{
	return s_footprint;
}


ClickableComponent::ClickableComponent(const Vector2d& size):
m_size(size)
{
	m_onClick = [](){};
	m_listener_id = InputManager::instance()->listen(
	[this](const hb::MouseButtonWorld& e)
	{
		hb::Vector3d p = getGameObject()->getPosition() + getPosition();
		if (e.x > p.x and e.x < p.x + m_size.x and e.y > p.y and e.y < p.y + m_size.y)
			m_onClick();
	});
}


ClickableComponent::~ClickableComponent()
{
	InputManager::instance()->ignore(m_listener_id);
}


void ClickableComponent::setOnClick(std::function<void(void)>&& onClick)
{
	m_onClick = std::move(onClick);
}


void ClickableComponent::setSize(const Vector2d& size)
{
	m_size = size;
}


const Vector2d& ClickableComponent::getSize() const
{
	return m_size;
}
