#ifndef SWITCH_COMPONENT
#define SWITCH_COMPONENT
#include "HB/Core.h"

class SwitchComponent : public hb::GameObject::Component
{
public:
	SwitchComponent(const std::string& target_name);
	~SwitchComponent();
	void setAction(std::function<void(hb::GameObject*)>&& action);
	bool isOn() const;
	void doSwitch();
private:
	std::function<void(hb::GameObject*)> m_action;
	std::string m_target_name;
	bool m_on;
};
#endif