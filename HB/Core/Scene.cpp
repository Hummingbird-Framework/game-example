#include "Game.h"
using namespace hb;

Game::Scene::Scene(const std::string& name, std::function<void(void)>&& init)
{
	m_init = std::move(init);
	m_exit = std::move([](){});
	m_name = name;
}

Game::Scene::Scene(const Scene& other)
{
	m_init = other.m_init;
	m_exit = other.m_exit;
	m_name = other.m_name;
}

Game::Scene::Scene(Scene&& other)
{
	m_init = std::move(other.m_init);
	m_exit = std::move(other.m_exit);
	m_name = other.m_name;
}


Game::Scene::~Scene()
{

}


GameObject* Game::Scene::makeGameObject(std::map<std::string, std::string>& properties)
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


void Game::Scene::init()
{
	m_init();
}


const std::string& Game::Scene::getName() const
{
	return m_name;
}


void Game::Scene::exit()
{
	m_exit();
}


void Game::Scene::setExit(std::function<void(void)>&& exit)
{
	m_exit = std::move(exit);
}
