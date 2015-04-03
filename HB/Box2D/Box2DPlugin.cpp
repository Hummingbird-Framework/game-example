#include "Box2DPlugin.h"
using namespace hb;

Box2DPlugin::Box2DPlugin():
m_time_left(Time::seconds(0))
{}


Box2DPlugin::~Box2DPlugin()
{}


void Box2DPlugin::preUpdate()
{
	m_time_left -= Time::deltaTime;
	if (m_time_left.asMicroseconds() > 0)
		return;
	Physics2d::getB2World()->Step(
		Physics2d::s_time_step.asSeconds(),
		Physics2d::s_vel_iterations,
		Physics2d::s_pos_iterations);
	Physics2d::s_instance.m_contact_listener->sendStayContact();
	m_time_left = Physics2d::s_time_step;
}
