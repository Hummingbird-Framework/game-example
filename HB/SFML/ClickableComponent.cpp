#include "ClickableComponent.h"
using namespace hb;


ClickableComponent::ClickableComponent():
ClickableComponent(hb::Vector2d())
{

}


ClickableComponent::ClickableComponent(const Vector2d& size):
m_size(size)
{
	m_onClick = [](){};
	m_listener_id = InputManager::instance()->listen(
	[this](hb::MouseButtonWorld& e)
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
