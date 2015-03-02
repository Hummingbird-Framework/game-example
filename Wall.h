#ifndef WALL
#define WALL
#include "HB/Base.h"
#include "HB/SFML.h"

class Wall : public hb::GameObject::Component
{
public:
	Wall(hb::RenderWindowManager* window_manager, const hb::Vector2d& size);
	~Wall() override;
	virtual void init() override;

private:
	hb::InputManager::ListenerId<hb::MouseButtonWorld> mousebuttonworld_listener_id;
	hb::CollisionComponent* m_collider;
	hb::SpriteComponent* m_sprite;
};

#endif