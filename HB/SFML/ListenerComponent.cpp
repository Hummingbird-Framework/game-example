#include "ListenerComponent.h"
using namespace hb;


ListenerComponent::ListenerComponent():
GameObject::Component()
{

}


ListenerComponent::~ListenerComponent()
{

}


void ListenerComponent::init()
{
	postUpdate();
}


void ListenerComponent::postUpdate()
{
	hb::Vector3d p = getGameObject()->getPosition();
	sf::Listener::setPosition(p.x, p.y, p.z);
}


void ListenerComponent::setDirection(const Vector3d& direction) const
{
	sf::Listener::setDirection(direction.x, direction.y, direction.z);
}
