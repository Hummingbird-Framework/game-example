#include "makeObjects.h"

hb::GameObject* makeBullet(const hb::Vector2d& direction)
{
	hb::Vector2d m_direction = direction.normalized();
	hb::Texture tex = hb::Texture::loadFromFile("res/drawable/fireballs.png", hb::Rect());
	hb::Sprite m_animation = hb::Sprite(tex, hb::Vector2d(16, 16), hb::Vector2d(0, 0));
	auto m_sprite = new hb::SpriteComponent(m_animation, {4, 5, 6, 7}, hb::Time::seconds(0.1));
	auto m_collision = new hb::CollisionComponent(hb::Vector2d(0.5, 0.5));
	hb::SoundBuffer sound_buffer = hb::SoundBuffer::loadFromFile("res/sound/Fire-ball.wav");
	hb::SoundComponent* sound = new hb::SoundComponent(sound_buffer);
	sound->play();
	sound->setRelativeToListener(true);

	auto bullet = new hb::GameObject
	{
		new hb::FunctionComponent(),
		m_sprite,
		m_collision,
		sound
	};
	bullet->setName("Fireball");
	auto fc = bullet->getComponent<hb::FunctionComponent>();
	struct Data
	{
		hb::Clock clock;
		hb::Time life_time;
	};
	Data* data = new Data;

	data->life_time = hb::Time::seconds(2);

	fc->setUpdateFunction([=]()
	{
		auto clk = data->clock;
		auto life_time = data->life_time;
		hb::Vector3d p = fc->getGameObject()->getPosition();
		fc->getGameObject()->setPosition((p + hb::Vector3d(m_direction, 0) * 500./32. *  hb::Time::deltaTime.asSeconds()));
		if (clk.getElapsedTime() > life_time)
		{
			fc->getGameObject()->destroy();
		}

		while(not m_collision->empty())
		{
			hb::CollisionComponent::Collision c = m_collision->nextCollision();
			if (c.object->getName() == "Wall")
			{
				fc->getGameObject()->destroy();
			}
		}
	});

	return bullet;
}