#include "Bullet.h"
Bullet::Bullet(hb::RenderWindowManager* window_manager, const hb::Vector2d& direction)
{
	m_direction = direction.normalized();
	m_animation = hb::SpriteComponent::Animation("res/drawable/fireballs.png", sf::IntRect(), hb::Vector2d(16, 16), hb::Vector2d(0, 0), 4, 7, hb::Time::seconds(0.1));
	m_sprite = new hb::SpriteComponent(window_manager, m_animation);
	m_collision = new hb::CollisionComponent(hb::Vector2d(16, 16));
	m_clock.reset();
	m_life_time = hb::Time::seconds(2);
}


Bullet::~Bullet()
{

}



void Bullet::init()
{
	getGameObject()->addComponent(m_sprite);
	getGameObject()->addComponent(m_collision);
	hb::SoundComponent* sound = new hb::SoundComponent();
	sound->setSound("res/sound/Fire-ball.wav");
	sound->getSound().play();
	getGameObject()->addComponent(sound);
}


void Bullet::update()
{
	hb::Vector3d p = getGameObject()->getPosition();
	getGameObject()->setPosition((p + hb::Vector3d(m_direction, 2) * 250 *  hb::Time::deltaTime.asSeconds()));
	if (m_clock.getElapsedTime() > m_life_time)
		getGameObject()->destroy();

	while(not m_collision->empty())
	{
		hb::CollisionComponent::Collision c = m_collision->nextCollision();
		if (c.object->getComponents<Wall>().size() != 0)
		{
			getGameObject()->destroy();
		}
	}
}
