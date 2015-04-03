#include <iostream>
#include "HB/Core.h"
#include "HB/SFML.h"
#include "makeObjects.h"
#include "HB/Tmx/TmxScene.h"

// Small plugin for printing the FPS on console
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
	// Create Game window
	hb::Renderer::createWindow(hb::Vector2d(1000, 700), "Game");
	// Set camera position
	hb::Renderer::getCamera().setPosition(hb::Vector3d());
	// Register SFML Plugin in Game (allows to update input and draw when necessary)
	hb::Game::addPlugin<hb::SFMLPlugin>();
	//hb::Game::addPlugin<FPSPlugin>();
	// Set Draw space director vectors
	// Scale 1:32 (Object space -> Draw space)
	hb::Renderer::getCamera().setAxisX(hb::Vector3d(32, 0, 0));
	hb::Renderer::getCamera().setAxisY(hb::Vector3d(0, 32, 0));
	hb::Renderer::getCamera().setAxisZ(hb::Vector3d(0, 0, 32));

	// Register Object factories for Tmx scenes
	hb::TmxRegisterFactory("Wall", makeWall);
	hb::TmxRegisterFactory("Player", makePlayer);
	hb::TmxRegisterFactory("Switch", makeSwitch);
	hb::TmxRegisterFactory("Bridge", makeBridge);
	hb::TmxRegisterFactory("Door", makeDoor);

	auto hb_scene = hb::Game::Scene("hb_intro", []()
	{
		hb::Texture tex = hb::Texture::loadFromFile("res/drawable/HB-logo2.png");
		hb::Sprite spr(tex);
		auto sprite = new hb::SpriteComponent(spr);
		sprite->setColor(hb::Color(1.f,1.f,1.f,0.f));
		auto fc = new hb::FunctionComponent();
		struct Data
		{
			hb::Time time_to_view;
			hb::Time time_wait;
			float alfa;
		};
		Data* data = new Data();
		data->time_to_view = hb::Time::seconds(2);
		data->time_wait = hb::Time::seconds(1);
		new hb::GameObject(
		{
			sprite,
			fc
		});
		fc->addListener("update", [=](hb::DataRepository&)
		{
			if (data->time_to_view > hb::Time())
			{
				if (data->time_wait > hb::Time())
				{
					data->time_to_view -= hb::Time::deltaTime;
					hb::Color c = sprite->getColor();
					c.a = 1.f - data->time_to_view.asSeconds()/2.;
					if (c.a > 1.f)
						c.a = 1.f;
					sprite->setColor(c);
				}
				else
				{
					data->time_to_view -= hb::Time::deltaTime;
					hb::Color c = sprite->getColor();
					c.a = data->time_to_view.asSeconds()/2.;
					sprite->setColor(c);
					if (data->time_to_view < hb::Time())
						hb::Game::setScene("demo");
				}
			}
			else
			{
				data->time_wait -= hb::Time::deltaTime;
				if (data->time_wait < hb::Time())
					data->time_to_view = hb::Time::seconds(2);
			}
		});

		fc->addListener("destroy", [=](hb::DataRepository&)
		{
			delete data;
		});

		hb::Renderer::getWindow().setSize(sf::Vector2u(sprite->getSize().x, sprite->getSize().y));
		hb::Renderer::getCamera().setPosition(hb::Renderer::getCamera().DrawspaceToObjectspace(hb::Vector3d(sprite->getSize().x/2., sprite->getSize().y/2., 0)));
		hb::Renderer::getWindow().setView(sf::View(sf::FloatRect(0, 0, sprite->getSize().x, sprite->getSize().y)));
	});
	hb::Game::addScene(hb_scene);

	// Add Scenes loaded from Tmx file to game
	std::function<void(const Tmx::Map*)> cam = [](const Tmx::Map* map)
	{
		//hb::Renderer::getWindow().setSize(sf::Vector2u(map->GetWidth() * map->GetTileWidth(), map->GetHeight() * map->GetTileHeight()));
		hb::Renderer::getCamera().setPosition(hb::Vector2d(map->GetWidth()/2., map->GetHeight()/2.));
		hb::Renderer::getWindow().setView(sf::View(sf::FloatRect(0, 0, map->GetWidth() * map->GetTileWidth(), map->GetHeight() * map->GetTileHeight())));
	};
	hb::Game::addScene(hb::TmxScene("demo", "res/levels/demo.tmx", cam));
	hb::Game::addScene(hb::TmxScene("demo2", "res/levels/demo2.tmx", cam));

	// Start Game
	hb::Game::setScene("hb_intro");
	hb::Game::run();

	return 0;
}
