#include "SwitchComponent.h"

SwitchComponent::SwitchComponent(const std::string& target_name):
m_action([](hb::GameObject*){}),
m_target_name(target_name),
m_on(false)
{

}


SwitchComponent::~SwitchComponent()
{

}


void SwitchComponent::setAction(std::function<void(hb::GameObject*)>&& action)
{
	m_action = std::move(action);
}


bool SwitchComponent::isOn() const
{
	return m_on;
}


void SwitchComponent::doSwitch()
{
	m_on = not m_on;
	auto targets = hb::GameObject::getGameObjectsByName(m_target_name);
	for(hb::GameObject* go : targets)
	{
		m_action(go);
	}
}
