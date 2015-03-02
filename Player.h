#ifndef PLAYER_H
#define PLAYER_H
#include "HB/Base.h"
#include "HB/SFML.h"
#include "Bullet.h"

class Player : public hb::GameObject::Component
{
public:
	Player(hb::RenderWindowManager* window_manager1);

	~Player();
	
	hb::Vector2d direction;
	double speed;
	bool running;

	void init() override;

	void update() override;
	void shoot();

private:
	hb::Vector2d last_direction;

	hb::InputManager::ListenerId<hb::KeyPressed> keypressed_listener_id;
	hb::InputManager::ListenerId<hb::KeyReleased> keyreleased_listener_id;
	hb::InputManager::ListenerId<hb::MouseButtonWorld> mousebuttonworld_listener_id;

	hb::SpriteComponent::Animation animation_up;
	hb::SpriteComponent::Animation animation_down;
	hb::SpriteComponent::Animation animation_left;
	hb::SpriteComponent::Animation animation_right;

	hb::SpriteComponent* player_sprite;
	hb::CollisionComponent* m_collision;

	hb::Vector3d last_position;

	hb::RenderWindowManager* window_manager1;
};
#endif
