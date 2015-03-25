#ifndef HB_GAME_H
#define HB_GAME_H
#include <cstdlib>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include "GameObject.h"
#include "Clock.h"
#include "Plugin.h"

namespace hb
{
	class Game
	{
	public:
		class Scene
		{
		public:
			Scene(const std::string& name, std::function<void(void)>&& init);
			Scene(const Scene& other);
			Scene(Scene&& other);
			~Scene();


			void init();
			void exit();
			const std::string& getName() const;
			void setExit(std::function<void(void)>&& exit);

		protected:
			std::function<void(void)> m_init, m_exit;
			std::string m_name;
		};

		~Game();

		static GameObject* makeGameObject(std::map<std::string, std::string>& properties);
		static void addScene(Scene&& scene);
		static void setScene(const std::string& name);
		static void run();
		static void running(bool running);
		static bool isRunning();
		template<typename T>
		static void addPlugin()
		{
			T* t = new T();
			s_plugins.push_back(t);
		}
		static std::map<std::string, Plugin::ComponentFactory> getAllComponentFactories();


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