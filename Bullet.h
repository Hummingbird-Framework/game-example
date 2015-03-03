#include "HB/Base.h"
#include "HB/SFML.h"
#include "Wall.h"

class Bullet : public hb::GameObject::Component
{
public:
	Bullet(hb::RenderWindowManager* window_manager, const hb::Vector2d& direction);
	~Bullet();

	void init() override;
	void update() override;

private:
	hb::Vector2d m_direction;
	hb::SpriteComponent* m_sprite;
	hb::CollisionComponent* m_collision;
	hb::SoundComponent* m_sound;
	hb::Clock m_clock;
	hb::Time m_life_time;
	hb::Sprite m_animation;
};