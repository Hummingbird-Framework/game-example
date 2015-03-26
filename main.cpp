#include <iostream>
#include <cstdlib>
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
	hb::Vector2d a,b,c;
	c = a-b;
	hb::Game::running(false);

	// Create Game window
	hb::Renderer::createWindow(hb::Vector2d(1280, 720), "Game");
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

	// Add Scenes loaded from Tmx file to game
	hb::Game::addScene(hb::TmxScene("demo", "res/levels/demo.tmx"));
	hb::Game::addScene(hb::TmxScene("demo2", "res/levels/demo2.tmx"));

	// Start Game
	hb::Game::setScene("demo");
	hb::Game::run();
}
