#include "GameObject.h"

using namespace hb;

int GameObject::s_game_object_identifier = 0;
std::unordered_map<int, GameObject*> GameObject::s_game_objects_by_id = std::unordered_map<int, GameObject*>();
std::unordered_map<std::string, std::vector<GameObject*>> GameObject::s_game_objects_by_name = std::unordered_map<std::string, std::vector<GameObject*>>();
DataRepository GameObject::s_data_repository;

void GameObject::setNextGameObjectId(int id)
{
	s_game_object_identifier = id;
}


GameObject* GameObject::getGameObjectById(int id)
{
	GameObject* go = nullptr;
	auto s = s_game_objects_by_id.find(id);
	if (s != s_game_objects_by_id.end())
		go = s->second;
	hb_assert(go != nullptr, "GameObject with id " << id << "does not exist.");
	return go;
}


const std::vector<GameObject*>& GameObject::getGameObjectsByName(const std::string& name)
{
	return s_game_objects_by_name[name];
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
		if (not it->second->isActive()) continue;
		it->second->preUpdate();
	}
	for (std::unordered_map<int, GameObject*>::iterator it = s_game_objects_by_id.begin(); it != s_game_objects_by_id.end(); it++)
	{
		if (not it->second->isActive()) continue;
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
		if (not it->second->isActive()) continue;
		it->second->postUpdate();
	}
}


GameObject::GameObject():
Transform(),
m_active(true),
m_marked_to_destroy(false),
m_message_manager()
{
	// Find next available id
	while (s_game_objects_by_id.find(s_game_object_identifier) != s_game_objects_by_id.end())
		++s_game_object_identifier;

	m_identifier = s_game_object_identifier++;
	s_game_objects_by_id.insert(std::pair<int, GameObject*>(m_identifier, this));
}


GameObject::GameObject(const std::initializer_list<Component*>& components):
GameObject()
{
	for (Component* c : components)
		addComponent(c);
}


GameObject::GameObject(int id):
Transform(),
m_active(true),
m_marked_to_destroy(false),
m_message_manager()
{
	hb_assert(s_game_objects_by_id.find(id) == s_game_objects_by_id.end(), "GameObject with id " << id << "already exists.");
	m_identifier = id;
	s_game_objects_by_id.insert(std::pair<int, GameObject*>(m_identifier, this));
}


GameObject::~GameObject()
{
	m_message_manager.message("destroy", s_data_repository);
	for (Component* component : m_components)
		delete component;
	m_components.clear();

	setName("");
	s_game_objects_by_id.erase(m_identifier);
}


int GameObject::getId() const
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
		std::vector<GameObject*>& vec = s->second;
		vec.erase(std::remove(vec.begin(), vec.end(), this), vec.end());
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


void GameObject::setActive(bool active)
{
	m_active = active;
}


bool GameObject::isActive() const
{
	return m_active;
}


void GameObject::preUpdate()
{
	for (Component* component : m_components)
		if (component->isActive())
			component->preUpdate();

	m_message_manager.message("pre-update", s_data_repository);
}


void GameObject::update()
{
	for (Component* component : m_components)
		if (component->isActive())
			component->update();

	m_message_manager.message("update", s_data_repository);
}


void GameObject::postUpdate()
{
	for (Component* component : m_components)
		if (component->isActive())
			component->postUpdate();

	m_message_manager.message("post-update", s_data_repository);
}


void GameObject::destroy()
{
	m_marked_to_destroy = true;
}


void GameObject::addComponent(Component* component)
{
	hb_assert(component != nullptr, "Trying to add a null component pointer to a GameObject.");
	m_components.push_back(component);
	component->setGameObject(this);
	component->init();
}


void GameObject::addComponents(const std::vector<Component*>& components)
{
	for (Component* c : components)
		addComponent(c);
}


void GameObject::sendMessage(const std::string& name, DataRepository& data)
{
	m_message_manager.message(name, data);
}
