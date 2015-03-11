#include <iostream>
#include "HB/Base.h"
#include "HB/SFML.h"
#include "makeObjects.h"

int main(int argc, char const *argv[])
{
	hb::Renderer::createWindow(hb::Vector2d(1280, 720), "Game");
	//hb::Renderer::getCamera().setAxisX(hb::Vector3d(1, 0, 0));
	//hb::Renderer::getCamera().setAxisY(hb::Vector3d(-1, 1, 0));
	//hb::Renderer::getCamera().setAxisZ(hb::Vector3d(0, 0, 0));
	makePlayer();
	makeWall(hb::Vector2d(50, 40), hb::Vector2d(10, 100));
	makeWall(hb::Vector2d(20, 140), hb::Vector2d(100, 10));

	hb::Clock clk;
	hb::Time lastTime = hb::Time::microseconds(clk.getElapsedTime().asMicroseconds());
	while(hb::Renderer::getWindow().isOpen())
	{
		hb::Time::deltaTime = hb::Time::microseconds(clk.getElapsedTime().asMicroseconds())-lastTime;
		lastTime = hb::Time::microseconds(clk.getElapsedTime().asMicroseconds());
		
		hb::InputManager::instance()->update();

	//	std::cout << player->getPosition().z << ", " << player->getPosition().y << std::endl;
		hb::GameObject::updateAll();
		hb::Renderer::draw();
	}
	hb::GameObject::destroyAll();
}