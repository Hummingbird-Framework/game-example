#ifndef SWITCH_COMPONENT
#define SWITCH_COMPONENT
#include "HB/Core.h"

class SwitchComponent : public hb::GameObject::Component
{
public:
	SwitchComponent(const std::vector<int>& targets);
	~SwitchComponent();
	void setAction(std::function<void(hb::GameObject*)>&& action);
	bool isOn() const;
	void doSwitch();
private:
	std::function<void(hb::GameObject*)> m_action;
	std::vector<int> m_targets;
	bool m_on;
};
#endif