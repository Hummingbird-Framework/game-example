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


GameObject* Game::makeGameObject(std::map<std::string, std::string>& properties)
{
	std::map<std::string, Plugin::ComponentFactory> list = Game::getAllComponentFactories();
	GameObject* go = new GameObject;
	for (auto it : list)
	{
		if (properties.find(it.first + ".count") != properties.end())
		{
			int count = atoi(properties[it.first + ".count"].c_str());
			for (int i = 0; i < count; ++i)
			{
				GameObject::Component* c = it.second(properties, i);
				go->addComponent(c);
			}
		}
	}
	return go;
}


void Game::addScene(Scene&& scene)
{
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
		p->gameEnd();

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


std::map<std::string, Plugin::ComponentFactory> Game::getAllComponentFactories()
{
	std::map<std::string, Plugin::ComponentFactory> ret;
	for (Plugin* p : s_plugins)
	{
		std::map<std::string, Plugin::ComponentFactory> list = p->getComponentFactory();
		ret.insert(list.begin(), list.end());
	}

	return ret;
}
