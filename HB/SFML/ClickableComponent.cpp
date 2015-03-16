#include "ClickableComponent.h"
#include <iostream>
using namespace hb;

ClickableComponent::ClickableComponent():
ClickableComponent(hb::Vector2d())
{

}


ClickableComponent::ClickableComponent(const Vector2d& size):
m_size(size)
{
	m_onClick = [](){std::cout << "hai2" << std::endl;};
	InputManager::instance()->listen(
	[this](const hb::MouseButtonWorld& e)
	{
		hb::Vector3d p = getGameObject()->getPosition() + getPosition();
		Camera& camera = Renderer::getCamera();
		p = (camera.getAxisX() * p.x) + (camera.getAxisY() * p.y) + (camera.getAxisZ() * p.z);
		hb::Vector2d size = ((camera.getAxisX() * m_size.x) + (camera.getAxisY() * m_size.y)).xy();
		if (e.x > p.x and e.x < p.x + size.x and e.y > p.y and e.y < p.y + size.y)
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
