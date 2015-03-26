#include <iostream>
#include <cstdlib>
#include "HB/Core.h"
#include "HB/SFML.h"
#include "makeObjects.h"
#include "HB/Tmx/TmxScene.h"


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
	hb::Vector2d a,b,c;
	c = a-b;
	hb::Game::running(false);
	hb::Renderer::createWindow(hb::Vector2d(1280, 720), "Game");
	hb::Renderer::getCamera().setPosition(hb::Vector3d());
	hb::Game::addPlugin<hb::SFMLPlugin>();
	//hb::Game::addPlugin<FPSPlugin>();
	// Perpectiva caballera
	//hb::Renderer::getCamera().setAxisX(hb::Vector3d(32, 0, 0));
	//hb::Renderer::getCamera().setAxisY(hb::Vector3d(-32, 32, 0));
	//hb::Renderer::getCamera().setAxisZ(hb::Vector3d(0, 0, 32));
	// Perspectiva isometrica
	//hb::Renderer::getCamera().setAxisX(hb::Vector3d(32, 16, 16));
	//hb::Renderer::getCamera().setAxisY(hb::Vector3d(-32, 16, 16));
	//hb::Renderer::getCamera().setAxisZ(hb::Vector3d(0, 0, 1));
	// Escala 1:32
	hb::Renderer::getCamera().setAxisX(hb::Vector3d(32, 0, 0));
	hb::Renderer::getCamera().setAxisY(hb::Vector3d(0, 32, 0));
	hb::Renderer::getCamera().setAxisZ(hb::Vector3d(0, 0, 32));

	hb::TmxRegisterFactory("Wall", makeWall);
	hb::TmxRegisterFactory("Player", makePlayer);
	hb::TmxRegisterFactory("Switch", makeSwitch);
	hb::TmxRegisterFactory("Bridge", makeBridge);
	hb::TmxRegisterFactory("Door", makeDoor);

	hb::Game::addScene(hb::TmxScene("demo", "res/levels/demo.tmx"));
	hb::Game::addScene(hb::TmxScene("demo2", "res/levels/demo2.tmx"));

	hb::Game::setScene("demo");
	hb::Game::run();
}
