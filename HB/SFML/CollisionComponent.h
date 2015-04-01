#ifndef HB_COLLISION_COMPONENT_H
#define HB_COLLISION_COMPONENT_H
#include <queue>
#include <set>
#include "../Core/Transform.h"
#include "../Core/GameObject.h"
#include "../Core/Vector2d.h"
#include "../Core/Vector3d.h"
#include "Rect.h"

namespace hb
{
	/**
	 * \class CollisionComponent
	 * \ingroup SFML-components
	 */
	class CollisionComponent : public GameObject::Component, public Transform
	{
	public:
		struct Collision
		{
			Rect intersection;
			GameObject* object;
		};
		CollisionComponent(const Vector2d& size = Vector2d());
		CollisionComponent(double width, double height);
		virtual ~CollisionComponent() override;

		virtual void preUpdate() override;
		virtual void postUpdate() override;
		void setSize(const Vector2d& box);
		const Vector2d& getSize() const;

		static void executeCollisions();

		Collision nextCollision();
		bool empty() const;

	private:
		static bool s_collisions_executed;
		static std::set<CollisionComponent*> s_components;

		Vector2d m_size;
		std::queue<Collision> m_collisions;
		std::set<CollisionComponent*>::iterator m_me;
	};
}
#endif