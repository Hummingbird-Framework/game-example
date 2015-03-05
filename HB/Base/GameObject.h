#ifndef HB_GAME_OBJECT_H
#define HB_GAME_OBJECT_H
#include <vector>
#include <string>
#include <unordered_map>
#include <initializer_list>
#include "Transform.h"
#include "DataRepository.h"
// TODO: Add to game object a std::unordered_map<std::string, union{.....}> to store gameobject variables. Make getters too.
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
				m_relative = true;
			}
			inline virtual ~Component(){}
			virtual void init(){}
			virtual void preUpdate(){}
			virtual void update(){}
			virtual void postUpdate(){}
			GameObject* getGameObject() const {return m_game_object;}

		private:
			void setGameObject(GameObject* game_object)
			{m_game_object = game_object;}
			GameObject* m_game_object;
			bool m_relative;
		};

		static GameObject* getGameObjectById(int id);
		static std::vector<GameObject*> getGameObjectsByName(const std::string& name);
		template <typename T>
		static std::vector<T*> getGameObjectsByName(const std::string& name)
		{
			std::vector<GameObject*> v;
			std::vector<T*> ts;
			
			auto s = s_game_objects_by_name.find(name);
			if (s != s_game_objects_by_name.end())
				v = s->second;

			for (GameObject* go : v)
			{
				T* t = dynamic_cast<T*>(go);
				if (t != nullptr)
					ts.push_back(t);
			}
			return ts;
		}
		static void destroyAll();
		static void updateAll();

		GameObject();
		GameObject(std::initializer_list<Component*> components);
		virtual ~GameObject();
		int getIdentifier() const;
		const std::string& getName() const;
		void setName(const std::string& name);
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
			std::vector<ComponentType*> v;
			for (Component* component : m_components)
			{
				if (dynamic_cast<ComponentType*>(component))
					v.push_back(dynamic_cast<ComponentType*>(component));
			}
			return v;
		}

	private:
		static int s_game_object_identifier;
		static std::unordered_map<int, GameObject*> s_game_objects_by_id;
		static std::unordered_map<std::string, std::vector<GameObject*>> s_game_objects_by_name;

		bool m_marked_to_destroy;
		int m_identifier;
		std::string m_name;
		std::vector<Component*> m_components;
	};
}
#endif
