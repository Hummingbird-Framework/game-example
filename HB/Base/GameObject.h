#ifndef HB_GAME_OBJECT_H
#define HB_GAME_OBJECT_H
#include <vector>
#include <string>
#include <unordered_map>
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
		};

		static GameObject* getGameObjectById(int id);
		static void getGameObjectsByName(const std::string& name, std::vector<GameObject*>& out);
		static void destroyAll();
		static void updateAll();

		GameObject();
		GameObject(const std::initializer_list<Component*>& components);
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
		void getComponents(std::vector<ComponentType*>& out) const
		{
			for (Component* component : m_components)
			{
				if (dynamic_cast<ComponentType*>(component))
					out.push_back(dynamic_cast<ComponentType*>(component));
			}
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
