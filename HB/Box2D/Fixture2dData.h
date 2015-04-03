#ifndef HB_FIXTURE_2D_DATA_H
#define HB_FIXTURE_2D_DATA_H
#include <string>

namespace hb
{
	class RigidBody2dComponent;
	struct Fixture2dData
	{
		unsigned int id;
		std::string name;
		RigidBody2dComponent* rigid_body;
	};
}
#endif