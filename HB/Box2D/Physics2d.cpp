#include "Physics2d.h"
using namespace hb;

hb::Physics2d hb::Physics2d::s_instance;
int hb::Physics2d::s_vel_iterations = 8;
int hb::Physics2d::s_pos_iterations = 3;
hb::Time hb::Physics2d::s_time_step = hb::Time::seconds(1./60.);