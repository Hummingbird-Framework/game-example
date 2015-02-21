#include "Bullet.h"

Bullet::Bullet(hb::RenderWindowManager* window_manager, const hb::Vector2d& direction)
{
	m_direction = direction.normalized();
	m_animation = hb::SpriteComponent::Animation("res/drawable/fireballs.png", sf::IntRect(), hb::Vector2d(16, 16), hb::Vector2d(0, 0), 4, 7, hb::Time::seconds(0.25));
	m_sprite = new hb::SpriteComponent(window_manager, m_animation);
	m_clock.reset();
	m_life_time = hb::Time::seconds(2);
}


Bullet::~Bullet()
{

}



void Bullet::init()
{
	getGameObject()->addComponent(m_sprite);
}


void Bullet::update()
{
	hb::Vector3d p = getGameObject()->getPosition();
	getGameObject()->setPosition((p + hb::Vector3d(m_direction, 2) * 100 *  hb::Time::deltaTime.asSeconds()));
	if (m_clock.getElapsedTime() > m_life_time)
		getGameObject()->destroy();
}
