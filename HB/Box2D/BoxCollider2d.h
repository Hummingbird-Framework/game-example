#ifndef HB_BOX_COLLIDER2D_H
#define HB_BOX_COLLIDER2D_H
#include <Box2D/Box2D.h>
#include "../Core/Vector2d.h"
#include "../Core/Math.h"
#include "Collider2d.h"

namespace hb
{
	class BoxCollider2d : public Collider2d
	{
	public:
		BoxCollider2d(const Material2d& material, const Vector2d& size, const Vector2d& center, double angle, bool is_sensor);
	};
}
#endif