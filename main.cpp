#include <iostream>
#include <cstdlib>
#include "HB/Core.h"
#include "HB/SFML.h"
#include "makeObjects.h"

hb::GameObject* makeRandomObject()
{
	hb::Sprite sprite(
		hb::Texture::loadFromFile("res/drawable/walking-tiles.png", hb::Rect(192, 0, 32*3, 32)),
		hb::Vector2d(32, 32), hb::Vector2d(),
		{0, 1, 2, 1},
		hb::Time::seconds(0.33)
	);
	//hb::SoundBuffer sound_buf = hb::SoundBuffer::loadFromFile("res/sound/beep.ogg");
	auto obj = new hb::GameObject
	{
		//new hb::CollisionComponent(hb::Vector2d(32, 32)),
		new hb::SpriteComponent(sprite),
		new hb::FunctionComponent(),
		//new hb::SoundComponent(sound_buf)
	};
	obj->setName("RandomObject");
	//auto collision = obj->getComponent<hb::CollisionComponent>();
	auto fc = obj->getComponent<hb::FunctionComponent>();
	//auto sound = obj->getComponent<hb::SoundComponent>();
	//sound->loop(false);

	struct Data // NOTE: No necesito DataRepository (?)
	{
		hb::Vector2d direction;
	};
	Data* data = new Data;

	data->direction = hb::Vector2d((double)(rand() % 100)/100., (double)(rand() % 100)/100.);

	obj->setPosition(hb::Vector2d(rand() % hb::Renderer::getWindow().getSize().x-32,
								  rand() % hb::Renderer::getWindow().getSize().y-32));

	fc->setUpdateFunction([=]()
	{
		hb::Vector2d& direction = data->direction;
		const hb::Vector3d& pos = obj->getPosition();
		/*while (not collision->empty())
		{
			collision->nextCollision();
			//if (sound->getStatus() != hb::SoundComponent::Playing and rand() % 10000 < 1)
			//	sound->play();
		}*/

		if (pos.x < 0 or pos.x + 32 > hb::Renderer::getWindow().getSize().x)
			direction.x *= -1;
		if (pos.y < 0 or pos.y + 32 > hb::Renderer::getWindow().getSize().y)
			direction.y *= -1;

		fc->getGameObject()->setPosition(pos + direction * 100. * hb::Time::deltaTime.asSeconds());
	});

	hb::InputManager::instance()->listen([=](const hb::KeyPressed& e)
	{
		if (e.code == hb::Keyboard::Key::Space)
			data->direction *= -1;
	});

	fc->setDestroyFunction(
	[=]()
	{
		delete data;
	});
	return obj;
}

int main(int argc, char const *argv[])
{
	srand (time(NULL));

	hb::Renderer::createWindow(hb::Vector2d(1280, 720), "Game");

	hb::Game::addPlugin<hb::SFMLPlugin>();

	hb::Game::addScene(hb::Scene("main",
	[=]()
	{
		// Perpectiva caballera
		//hb::Renderer::getCamera().setAxisX(hb::Vector3d(1, 0, 0));
		//hb::Renderer::getCamera().setAxisY(hb::Vector3d(-1, 1, 0));
		//hb::Renderer::getCamera().setAxisZ(hb::Vector3d(0, 0, 0));
		// Perspectiva isometrica
		//hb::Renderer::getCamera().setAxisX(hb::Vector3d(1, 0.5, 0.5));
		//hb::Renderer::getCamera().setAxisY(hb::Vector3d(-1, 0.5, 0.5));
		//hb::Renderer::getCamera().setAxisZ(hb::Vector3d(0, 0, 0));
		makePlayer();
		makeWall(hb::Vector2d(50, 40), hb::Vector2d(64, 64));
		makeWall(hb::Vector2d(70, 140), hb::Vector2d(64, 64));

		int N = 20000;
		for (int i = 0; i < N; ++i)
		{
			makeRandomObject();
		}
	}));
	hb::Game::setScene("main");
	hb::Game::run();
}
