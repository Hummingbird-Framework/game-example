#ifndef HB_CIRCLE_COLLIDER2D_H
#define HB_CIRCLE_COLLIDER2D_H
#include <Box2D/Box2D.h>
#include "../Core/Vector2d.h"
#include "Collider2d.h"

namespace hb
{
	class CircleCollider2d : public Collider2d
	{
	public:
		CircleCollider2d(const Material2d& material, const Vector2d& center, double radius, bool is_sensor);
	};
}
#endif