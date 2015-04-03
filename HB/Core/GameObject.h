#ifndef HB_GAME_OBJECT_H
#define HB_GAME_OBJECT_H
#include <algorithm>
#include <initializer_list>
#include <map>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>
#include "DataRepository.h"
#include "Log.h"
#include "MessageManager.h"
#include "Transform.h"

namespace hb
{
	/*!
	  \brief Definition of the MessageManager used by GameObject
	*/
	typedef MessageManager<DataRepository> GameObjectMessageManager;
	/*!
	  \class GameObject
	  \ingroup core
	  \brief GameObject (also known as Actor).

	  This class creates a object in the Game. It, by default, doesn't have any behaviour 
	  and __you should not inherit from it__. Instead GameObjects are composed by Component%s.

	  These Component%s are the ones that must implement the behaviour of the GameObject composed by them.

	  GameObject%s are identified by a unique __id__ that is assigned to every GameObject created 
	  and you can get it by querying its id (see getGameObjectById()). 
	  They can also be grouped by __name__, that is, you can set the same name to a group of GameObject%s 
	  and later you can get them all by querying their name (see getGameObjectsByName()).

	  The Update of a GameObject consists in three steps: __pre-update__, __update__ and __post-update__. 
	  These are used for respectively running its Component%s __pre-update__, __update__ and __post-update__ 
	  functions. The GameObject will also send a message to its MessageManager with the name of the event 
	  ("pre-update", "update" and "post-update") with an empty DataRepository as the parameter.

	  To __destroy__ a GameObject you __must__ call destroy(), not its destructor. The GameObject then, will 
	  be marked to be destroyed and after the next update step it'll be deleted. Just before being deleted, 
	  the GameObject will send a message to its MessageManager with the name "destroy" and an empty DataRepository 
	  as the parameter.

	  A GameObject can be __active__ or __inactive__. If a GameObject is __inactive__ it exists, 
	  has a unique id and may be grouped by name; all its Component%s also exist and have been 
	  instantiated. But it __won't__ be updated. Same applies to Components.
	*/
	class GameObject : public Transform
	{
	public:
		/*!
		  \class Component
		  \brief Base class for implementing custom Component%s.
		*/
		class Component
		{
		public:
			friend class GameObject;
			/*!
			  \brief Default constructor.

			  At this point getGameObject() is pointing to nothing.
			*/
			Component():
			m_active(true),
			m_game_object(nullptr)
			{}
			/*!
			  \brief Default destructor.
			*/
			virtual ~Component(){}
			/*!
			  \brief Function called once after the Component has been added to a GameObject.

			  At this point getGameObject() returns a pointer to the containing GameObject instance.
			*/
			virtual void init(){}
			/*!
			  \brief Function called in the pre-update step.
			*/
			virtual void preUpdate(){}
			/*!
			  \brief Function called in the update step.
			*/
			virtual void update(){}
			/*!
			  \brief Function called in the post-update step.
			*/
			virtual void postUpdate(){}
			/*!
			  \brief Get the GameObject instance composed by this Component.
			  \return Pointer to GameObject instance composed by the Component, 
			  if it has already been added to a GameObject; nullptr otherwise.
			*/
			GameObject* getGameObject() const {return m_game_object;}
			/*!
			  \brief Set if Component is active.
			  \param active Is Component active.
			*/
			void setActive(bool active)
			{m_active = active;}
			/*!
			  \brief Get if Component is active.
			  \return Is Component active.
			*/
			bool isActive() const
			{return m_active;}

		protected:
			void addListenerToGameObject(const std::string& name, std::function<void(DataRepository&)>&& listener)
			{
				hb_assert(m_game_object != nullptr, "Accessing Component's GameObject before being assigned.");
				getGameObject()->m_message_manager.listen(name, std::move(listener));
			}
			void ignoreToGameObject(const GameObjectMessageManager::ListenerId<DataRepository>& listener_id)
			{
				hb_assert(m_game_object != nullptr, "Accessing Component's GameObject before being assigned.");
				getGameObject()->m_message_manager.ignore(listener_id);
			}

		private:
			void setGameObject(GameObject* game_object)
			{m_game_object = game_object;}

			bool m_active;
			GameObject* m_game_object;
		};

		/*!
		  \brief Get GameObject instance given its id.
		  \param id GameObject id.
		  \return Pointer to GameObject instance.
		*/
		static GameObject* getGameObjectById(int id);
		/*!
		  \brief Get vector of GameObject%s with the given name.
		  \param name Name of the GameObject%s.
		  \return Vector of pointers to the GameObject%s matching the given name.
		*/
		static const std::vector<GameObject*>& getGameObjectsByName(const std::string& name);
		/*!
		  \brief Destroy all existing GameObjects.
		*/
		static void destroyAll();
		/*!
		  \brief Run the Update for all existing GameObjects.
		*/
		static void updateAll();

		/*!
		  \brief Default constructor.
		*/
		GameObject();
		/*!
		  \brief Class constructor. Adds all given components to the new GameObject instance.
		  \param components List of components to be added to the new GameObject.
		*/
		GameObject(const std::initializer_list<Component*>& components);
		/*!
		  \brief Class destructor.

		  It takes care of the destruction of all Component%s assigned to the GameObject.
		*/
		~GameObject();
		/*!
		  \brief Get the GameObject%'s id.
		  \return The GameObject%'s id.
		*/
		int getId() const;
		/*!
		  \brief Get the GameObject%'s name.
		  \return The GameObject%'s name.
		*/
		const std::string& getName() const;
		/*!
		  \brief Set the GameObject%'s name.
		*/
		void setName(const std::string& name);
		/*!
		  \brief Set if GameObject is active.
		  \param active Is GameObject active.
		*/
		void setActive(bool active);
		/*!
		  \brief Get if GameObject is active.
		  \return Is GameObject active.
		*/
		bool isActive() const;
		/*!
		  \brief Runs all its Component%'s preUpdate().
		*/
		void preUpdate();
		/*!
		  \brief Runs all its Component%'s update().
		*/
		void update();
		/*!
		  \brief Runs all its Component%'s postUpdate().
		*/
		void postUpdate();
		/*!
		  \brief Marks the GameObject to be destroyed.

		  The GameObject will be destroyed if it is marked to be destroyed after the update step.
		*/
		void destroy();
		/*!
		  \brief Add a Component to the GameObject.
		*/
		void addComponent(Component* component);
		/*!
		  \brief Add a group of Component%s to the GameObject.
		*/
		void addComponents(const std::vector<Component*>& components);
		/*!
		  \brief Get first Component of type ComponentType.
		  \tparam ComponentType Type of the Component to be retrieved.
		  \return Pointer to a ComponentType instance, or nullptr if there is none.
		*/
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
		/*!
		  \brief Get all Component%s of type ComponentType.
		  \tparam ComponentType Type of the Component%s to be retrieved.
		  \return Vector of pointers to ComponentType instances, empty vector if none.
		*/
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
		/*!
		  \brief Send message to this GameObject%'s Component%s
		*/
		void sendMessage(const std::string& name, DataRepository& data);
		/*!
		  \name Advanced usage

		  Used for messing with the unique id system of the GameObject%s.
		  @{
		*/
		/*!
		  \brief Set next GameObject id.
		  \param id Next GameObject id

		  The auto-increment of the GameObject unique id will start from __id__ 
		  after this is set.
		*/
		static void setNextGameObjectId(int id);
		/*!
		  \brief Class constructor for manually setting the GameObject id.
		*/
		GameObject(int id);
		//! @}

	private:
		static int s_game_object_identifier;
		static std::unordered_map<int, GameObject*> s_game_objects_by_id;
		static std::unordered_map<std::string, std::vector<GameObject*>> s_game_objects_by_name;
		static DataRepository s_data_repository;

		bool m_active, m_marked_to_destroy;
		int m_identifier;
		std::string m_name;
		std::vector<Component*> m_components;
		GameObjectMessageManager m_message_manager;
	};
}
#endif
