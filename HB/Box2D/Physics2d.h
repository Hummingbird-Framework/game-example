#ifndef HB_PHYSICS2D_H
#define HB_PHYSICS2D_H
#include <Box2D/Box2D.h>
#include "../Core/Time.h"
#include "ContactListener2d.h"

namespace hb
{
	class Physics2d
	{
	public:
		friend class Box2DPlugin;
		~Physics2d()
		{
			delete m_b2_world;
			delete m_contact_listener;
		}

		static b2World* getB2World()
		{return s_instance.m_b2_world;}

		static void setTimeStep(const Time& step)
		{s_time_step = step;}

		static void setVelocityIterations(int iterations)
		{s_vel_iterations = iterations;}

		static void setPositionIterations(int iterations)
		{s_pos_iterations = iterations;}

	private:
		Physics2d():
		m_b2_world(new b2World(b2Vec2())),
		m_contact_listener(new ContactListener2d)
		{
			m_b2_world->SetContactListener(m_contact_listener);
		}

		static Physics2d s_instance;
		static int s_vel_iterations;
		static int s_pos_iterations;
		static Time s_time_step;

		b2World* m_b2_world;
		ContactListener2d* m_contact_listener;
	};
}
#endif