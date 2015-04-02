#ifndef HB_GAME_H
#define HB_GAME_H
#include <functional>
#include <string>
#include <vector>
#include <map>
#include "GameObject.h"
#include "Clock.h"
#include "Plugin.h"
#include "Log.h"

namespace hb
{
	/*!
	  \class Game
	  \ingroup core
	  \brief Game class.

	  This class handles the gameloop and the change of Scene.

	  You may add Plugins to add function calls to the gameloop (see Plugin).
	*/
	class Game
	{
	public:
		/*!
		  \class Scene
		  \ingroup core
		  \brief Scene of a Game.

		  This class should initialize the GameObject%s that participate in this Scene, 
		  set global values, etc.
		*/
		class Scene
		{
		public:
			/*!
			  \brief Class constructor.
			  \param name Name of the Scene. It must be unique per Game.
			  \param init Function to be executed when the Scene is set.
			*/
			Scene(const std::string& name, std::function<void(void)>&& init);
			/*!
			  \brief Copy constructor of Scene.
			  \param other Original Scene
			*/
			Scene(const Scene& other);
			/*!
			  \brief Move constructor of Scene.
			  \param other Original Scene
			*/
			Scene(Scene&& other);
			/*!
			  \brief Class destructor.
			*/
			~Scene();

			/*!
			  \brief Called when Scene is being set.
			*/
			void init();
			/*!
			  \brief Called when Scene is being unset 
			  (Game is changing the current Scene or Game is ending).
			*/
			void exit();
			/*!
			  \brief Get Scene%'s name.
			*/
			const std::string& getName() const;
			/*!
			  \brief Set Scene's exit function.
			*/
			void setExit(std::function<void(void)>&& exit);

		protected:
			std::function<void(void)> m_init, m_exit;
			std::string m_name;
		};

		~Game();
		/*!
		  \brief Add a Scene to the Game.
		  \param scene Scene being added to the Game.
		*/
		static void addScene(Scene& scene);
		/*!
		  \brief Add a Scene to the Game.
		  \param scene Scene being added to the Game.
		*/
		static void addScene(Scene&& scene);
		/*!
		  \brief Set Scene with name _name_ as the current Scene.
		  \param name Name of the Scene the Game will change to.

		  Actually this method doesn't change immediatly the current scene, 
		  but it flags that the scene must be changed and the Game will do it when 
		  it fits its loop.

		  The methods Scene::init() and Scene::exit() are appropriately called.
		*/
		static void setScene(const std::string& name);
		/*!
		  \brief Run the Game.

		  Call this method when all Scene%s and Plugin%s are already added to the Game 
		  and it is ready to launch.
		*/
		static void run();
		/*!
		  \brief Set if the Game is running.
		  \param running Is Game running.

		  If _running_ is false the Game will exit the gameloop after the current 
		  iteration and will proceed to exit.
		*/
		static void running(bool running);
		/*!
		  \brief Get if the Game is running.
		  \return Is Game running.
		*/
		static bool isRunning();
		/*!
		  \brief Add Plugin to the Game.
		  \tparam T Type of the Plugin being added.

		  The plugin is instantiated using _T_'s default constructor and added to the Game.
		*/
		template<typename T>
		static void addPlugin()
		{
			T* t = new T();
			s_plugins.push_back(t);
		}


	private:
		Game();
		static void changeScene();

		static bool s_game_running, s_change_scene;
		static std::map<std::string, Scene>::iterator s_current_scene, s_next_scene;
		static std::map<std::string, Scene> s_scenes;
		static std::vector<Plugin*> s_plugins;
	};
}
#endif