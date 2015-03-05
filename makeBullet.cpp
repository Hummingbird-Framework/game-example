#include "makeObjects.h"

hb::GameObject* makeBullet(hb::RenderWindowManager* window_manager, const hb::Vector2d& direction)
{
	hb::Vector2d m_direction = direction.normalized();
	hb::Texture tex = hb::Texture::loadFromFile("res/drawable/fireballs.png", hb::Rect());
	hb::Sprite m_animation = hb::Sprite(tex, hb::Vector2d(16, 16), hb::Vector2d(0, 0), 4, 7, hb::Time::seconds(0.1));
	auto m_sprite = new hb::SpriteComponent(window_manager, m_animation);
	auto m_collision = new hb::CollisionComponent(hb::Vector2d(16, 16));
	hb::SoundComponent* sound = new hb::SoundComponent();
	sound->setSound("res/sound/Fire-ball.wav");
	sound->getSound().play();

	auto bullet = new hb::GameObject
	{
		new hb::FunctionComponent(),
		m_sprite,
		m_collision,
		sound
	};

	auto fc = bullet->getComponent<hb::FunctionComponent>();
	fc->run([fc]()
	{
		hb::Time* life_time = new hb::Time;
		*life_time = hb::Time::seconds(2);
		fc->setPointer("clock", new hb::Clock);
		fc->setPointer("life_time", life_time);
	});

	fc->setUpdateFunction([fc, m_collision, m_direction]()
	{
		auto clk = fc->getPointer<hb::Clock>("clock");
		auto life_time = fc->getPointer<hb::Time>("life_time");
		hb::Vector3d p = fc->getGameObject()->getPosition();
		fc->getGameObject()->setPosition((p + hb::Vector3d(m_direction, 2) * 250 *  hb::Time::deltaTime.asSeconds()));
		if (clk->getElapsedTime() > *life_time)
			fc->getGameObject()->destroy();

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