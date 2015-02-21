#include "GameObject.h"

using namespace hb;

int GameObject::s_game_object_identifier = 0;
std::unordered_map<int, GameObject*> GameObject::s_game_objects_by_id = std::unordered_map<int, GameObject*>();
std::unordered_map<std::string, std::vector<GameObject*>> GameObject::s_game_objects_by_name = std::unordered_map<std::string, std::vector<GameObject*>>();

GameObject* GameObject::getGameObjectById(int id)
{
	GameObject* go = nullptr;
	auto s = s_game_objects_by_id.find(id);
	if (s != s_game_objects_by_id.end())
		go = s->second;

	return go;
}


std::vector<GameObject*> GameObject::getGameObjectsByName(const std::string& name)
{
	std::vector<GameObject*> v;
	
	auto s = s_game_objects_by_name.find(name);
	if (s != s_game_objects_by_name.end())
		v = s->second;
	return v;
}


void GameObject::destroyAll()
{
	std::vector<std::pair<int, GameObject*>> v(s_game_objects_by_id.begin(), s_game_objects_by_id.end());
	s_game_objects_by_id.clear();
	s_game_objects_by_name.clear();
	for (std::pair<int, GameObject*> go : v)
		delete go.second;
}


void GameObject::updateAll()
{
	std::vector<GameObject*> to_destroy;
	for (std::unordered_map<int, GameObject*>::iterator it = s_game_objects_by_id.begin(); it != s_game_objects_by_id.end(); it++)
	{
		it->second->preUpdate();
	}
	for (std::unordered_map<int, GameObject*>::iterator it = s_game_objects_by_id.begin(); it != s_game_objects_by_id.end(); it++)
	{
		it->second->update();
		if (it->second->m_marked_to_destroy)
		{
			to_destroy.push_back(it->second);
		}
	}
	for (GameObject* go : to_destroy)
	{
		delete go;
	}
	for (std::unordered_map<int, GameObject*>::iterator it = s_game_objects_by_id.begin(); it != s_game_objects_by_id.end(); it++)
	{
		it->second->postUpdate();
	}
}


GameObject::GameObject():
Transform(),
m_marked_to_destroy(false)
{
	m_identifier = s_game_object_identifier++;
	s_game_objects_by_id.insert(std::pair<int, GameObject*>(m_identifier, this));
}


GameObject::GameObject(std::initializer_list<GameObject::Component*> components):
GameObject()
{
	for (Component* c : components)
	{
		addComponent(c);
	}
}


GameObject::~GameObject()
{
	for (Component* component : m_components)
		delete component;
	m_components.clear();

	s_game_objects_by_id.erase(m_identifier);

	auto s = s_game_objects_by_name.find(m_name);
	if (s != s_game_objects_by_name.end())
	{
		bool done = false;
		for (std::vector<GameObject*>::iterator i = s->second.begin(); i != s->second.end() and not done; ++i)
		{
			if ((*i)->getIdentifier() == getIdentifier())
			{
				done = true;
				s->second.erase(i);
			}
		}
		if (done and s->second.size() == 0)
		{
			s_game_objects_by_name.erase(m_name);
		}
	}
}


int GameObject::getIdentifier() const
{
	return m_identifier;
}


const std::string& GameObject::getName() const
{
	return m_name;
}


void GameObject::setName(const std::string& name)
{
	// Remove from existing name group
	auto s = s_game_objects_by_name.find(m_name);
	if (s != s_game_objects_by_name.end())
	{
		for (std::vector<GameObject*>::iterator i = s->second.begin(); i != s->second.end(); ++i)
		{
			if (*i == this)
			{
				s->second.erase(i);
				i = s->second.end();
			}
		}
		if (s->second.size() == 0)
		{
			s_game_objects_by_name.erase(m_name);
		}
	}

	// Add to new name group
	if (name != "")
	{
		m_name = name;
		auto go_group = s_game_objects_by_name.find(name);
		if (go_group == s_game_objects_by_name.end())
		{
			std::vector<GameObject*> go_vect;
			go_vect.push_back(this);
			s_game_objects_by_name.insert(std::pair<std::string, std::vector<GameObject*>>(m_name, go_vect));
		}
		else
		{
			go_group->second.push_back(this);
		}
	}
}


void GameObject::preUpdate()
{
	for (Component* component : m_components)
		component->preUpdate();
}


void GameObject::update()
{
	for (Component* component : m_components)
		component->update();
}


void GameObject::postUpdate()
{
	for (Component* component : m_components)
		component->postUpdate();
}


void GameObject::destroy()
{
	m_marked_to_destroy = true;
}


void GameObject::addComponent(Component* component)
{
	m_components.push_back(component);
	component->setGameObject(this);
	component->init();
}
