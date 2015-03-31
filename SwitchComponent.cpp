#include "SwitchComponent.h"

SwitchComponent::SwitchComponent(const std::vector<int>& targets):
m_action([](hb::GameObject*){}),
m_targets(targets),
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
	for (int id : m_targets)
	{
		auto go = hb::GameObject::getGameObjectById(id);
		m_action(go);
	}
}
