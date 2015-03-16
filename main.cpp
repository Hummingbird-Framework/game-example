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

class FPSPlugin : public hb::Plugin
{
public:
	FPSPlugin(){}
	~FPSPlugin(){}
	
	void preUpdate() override
	{
		std::cout << "FPS: " << 1./hb::Time::deltaTime.asSeconds() << std::endl;
	}
};

int main(int argc, char const *argv[])
{
	srand (time(NULL));

	hb::Renderer::createWindow(hb::Vector2d(1280, 720), "Game");
	hb::Renderer::getCamera().setPosition(hb::Vector3d());
	hb::Game::addPlugin<hb::SFMLPlugin>();
	//hb::Game::addPlugin<FPSPlugin>();
	// Perpectiva caballera
	//hb::Renderer::getCamera().setAxisX(hb::Vector3d(1, 0, 0));
	//hb::Renderer::getCamera().setAxisY(hb::Vector3d(-1, 1, 0));
	//hb::Renderer::getCamera().setAxisZ(hb::Vector3d(0, 0, 0));
	// Perspectiva isometrica
	hb::Renderer::getCamera().setAxisX(hb::Vector3d(32, 16, 16));
	hb::Renderer::getCamera().setAxisY(hb::Vector3d(-32, 16, 16));
	hb::Renderer::getCamera().setAxisZ(hb::Vector3d(0, 0, 1));
	// Escala 1:32
	//hb::Renderer::getCamera().setAxisX(hb::Vector3d(32, 0, 0));
	//hb::Renderer::getCamera().setAxisY(hb::Vector3d(0, 32, 0));
	//hb::Renderer::getCamera().setAxisZ(hb::Vector3d(0, 0, 32));

	hb::Game::addScene(hb::Scene("main",
	[=]()
	{
		makePlayer();
		makeWall(hb::Vector2d(0, (hb::Renderer::getWindow().getSize().y-10)/32.), hb::Vector2d(hb::Renderer::getWindow().getSize().x/32., 0.2));
		hb::Texture tex = hb::Texture::loadFromFile("");
		tex.repeat(true);
		auto collisions = new hb::CollisionComponent(hb::Vector2d(2, 2));
		auto clickable = new hb::ClickableComponent(hb::Vector2d(2, 2));
		clickable->setOnClick(
		[]()
		{
			std::cout << "hai1" << std::endl;
			hb::Game::setScene("second");
		});
		new hb::GameObject
		{
			collisions, new hb::SpriteComponent(tex), clickable
		};
	}));
	hb::Game::addScene(hb::Scene("second",
	[=]()
	{
		makePlayer();
		makeWall(hb::Vector2d(0, (hb::Renderer::getWindow().getSize().y-10)/32.), hb::Vector2d(hb::Renderer::getWindow().getSize().x/32., 0.2));
		makeWall(hb::Vector2d(0, (hb::Renderer::getWindow().getSize().y)/32. - 1), hb::Vector2d(2, 2));
		//makeWall(hb::Vector2d(70, 140), hb::Vector2d(64, 64));
	}));
	hb::Game::setScene("main");
	hb::Game::run();
}
