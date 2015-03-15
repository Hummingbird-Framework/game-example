#ifndef HB_GAME_OBJECT_H
#define HB_GAME_OBJECT_H
#include <cassert>
#include <vector>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <initializer_list>
#include "Transform.h"

namespace hb
{
	class GameObject : public Transform
	{
	public:
		class Component
		{
		public:
			friend class GameObject;
			Component()
			{
				m_game_object = nullptr;
			}
			virtual ~Component(){}
			virtual void init(){}
			virtual void preUpdate(){}
			virtual void update(){}
			virtual void postUpdate(){}
			GameObject* getGameObject() const {return m_game_object;}

		private:
			void setGameObject(GameObject* game_object)
			{m_game_object = game_object;}
			GameObject* m_game_object;
		};

		static GameObject* getGameObjectById(int id);
		static const std::vector<GameObject*>& getGameObjectsByName(const std::string& name);
		static void destroyAll();
		static void updateAll();

		GameObject();
		GameObject(const std::initializer_list<Component*>& components);
		~GameObject();
		int getIdentifier() const;
		const std::string& getName() const;
		void setName(const std::string& name);
		void setActive(bool active);
		bool isActive() const;
		void preUpdate();
		void update();
		void postUpdate();
		void destroy();
		void addComponent(Component* component);
		template <typename ComponentType>
		ComponentType* getComponent() const
		{
			for (Component* component : m_components)
			{
				if (dynamic_cast<ComponentType*>(component))
					return dynamic_cast<ComponentType*>(component);
			}
			return nullptr;
		}
		template <typename ComponentType>
		std::vector<ComponentType*> getComponents() const
		{
			std::vector<ComponentType*> r;
			for (Component* component : m_components)
			{
				if (dynamic_cast<ComponentType*>(component))
					r.push_back(dynamic_cast<ComponentType*>(component));
			}
			return r;
		}

	private:
		static int s_game_object_identifier;
		static std::unordered_map<int, GameObject*> s_game_objects_by_id;
		static std::unordered_map<std::string, std::vector<GameObject*>> s_game_objects_by_name;

		bool m_active, m_marked_to_destroy;
		int m_identifier;
		std::string m_name;
		std::vector<Component*> m_components;
	};
}
#endif
