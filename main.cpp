#include <iostream>
#include <cstdlib>
#include "HB/Base.h"
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

	struct Data // NOTE: No necesito DataRepository
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

	std::cout << "TextureManager: " << hb::TextureManager::instance()->size() << std::endl;
	std::cout << "SoundManager: " << hb::SoundManager::instance()->size() << std::endl;

	sf::ConvexShape back (4);
	back.setPoint(0, sf::Vector2f());
	hb::Vector3d p1 = (hb::Renderer::getCamera().getAxisX() * hb::Renderer::getWindow().getSize().x);
	back.setPoint(1, sf::Vector2f(p1.x, p1.y));
	hb::Vector3d p2 = (hb::Renderer::getCamera().getAxisY() * hb::Renderer::getWindow().getSize().y);
	back.setPoint(3, sf::Vector2f(p2.x, p2.y));
	p1 = p1 + p2;
	back.setPoint(2, sf::Vector2f(p1.x, p1.y));
	back.setFillColor(sf::Color(255, 255, 0));

	hb::Vector2d center(hb::Renderer::getWindow().getSize().x/2, hb::Renderer::getWindow().getSize().y/2);
	hb::Renderer::getCamera().setPosition(center);

	hb::Clock clk;
	hb::Time lastTime = hb::Time::microseconds(clk.getElapsedTime().asMicroseconds());
	while(hb::Renderer::getWindow().isOpen())
	{
		hb::Time::deltaTime = hb::Time::microseconds(clk.getElapsedTime().asMicroseconds())-lastTime;
		lastTime = hb::Time::microseconds(clk.getElapsedTime().asMicroseconds());
		
		hb::InputManager::instance()->update();
		std::cout << "FPS: " << 1./hb::Time::deltaTime.asSeconds() << std::endl;
		//std::cout << "window: " << hb::Renderer::getWindow().getSize().x << ", " << hb::Renderer::getWindow().getSize().y << std::endl;
		//std::cout << "player: " << player->getPosition().x << ", " << player->getPosition().y << std::endl;
		hb::GameObject::updateAll();
		hb::Renderer::addDrawable(std::pair<hb::Vector3d, sf::Drawable*>(hb::Vector3d(0,0,-1000), &back));
		hb::Renderer::draw();
	}
	hb::GameObject::destroyAll();
}