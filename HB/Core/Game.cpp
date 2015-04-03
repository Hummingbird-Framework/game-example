#include "Game.h"
using namespace hb;


bool Game::s_game_running = false;
bool Game::s_change_scene = false;
std::map<std::string, Game::Scene> Game::s_scenes;
std::map<std::string, Game::Scene>::iterator Game::s_current_scene = Game::s_scenes.end();
std::map<std::string, Game::Scene>::iterator Game::s_next_scene = Game::s_scenes.end();
std::vector<Plugin*> Game::s_plugins;


Game::Game()
{

}


Game::~Game()
{
	for (Plugin* p : s_plugins)
		delete p;
}


void Game::addScene(Scene& scene)
{
	hb_assert(s_scenes.find(scene.getName()) == s_scenes.end(), "Scene with name `" << scene.getName() << "` already added.");
	s_scenes.insert(std::pair<std::string, Scene>(scene.getName(), scene));
}


void Game::addScene(Scene&& scene)
{
	hb_assert(s_scenes.find(scene.getName()) == s_scenes.end(), "Scene with name `" << scene.getName() << "` already added.");
	s_scenes.insert(std::pair<std::string, Scene>(scene.getName(), scene));
}


void Game::setScene(const std::string& name)
{
	auto it = s_scenes.find(name);
	hb_assert(it != s_scenes.end(), "Scene with name " << name << "does not exist.");
	s_change_scene = true;
	s_next_scene = it;
}


void Game::changeScene()
{
	if (s_current_scene != s_scenes.end())
		s_current_scene->second.exit();
	hb::GameObject::destroyAll();
	s_current_scene = s_next_scene;
	s_change_scene = false;
	s_current_scene->second.init();
}


void Game::run()
{
	hb_assert(s_change_scene, "Initial Game scene not defined.");
	s_game_running = true;

	for (Plugin* p : s_plugins)
		p->gameStart();

	hb::Clock clk;
	while(s_game_running)
	{
		hb::Time::deltaTime = clk.reset();
		if (s_change_scene)
		{
			changeScene();
			clk.reset();
		}

		for (Plugin* p : s_plugins)
			p->preUpdate();

		hb::GameObject::updateAll();

		for (Plugin* p : s_plugins)
			p->postUpdate();

	}
	s_current_scene->second.exit();

	for (Plugin* p : s_plugins)
	{
		p->gameEnd();
		delete p;
	}

	hb::GameObject::destroyAll();
}


void Game::running(bool running)
{
	s_game_running = running;
}


bool Game::isRunning()
{
	return s_game_running;
}
