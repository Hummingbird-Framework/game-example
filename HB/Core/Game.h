#ifndef HB_GAME_H
#define HB_GAME_H
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include "Scene.h"
#include "GameObject.h"
#include "Clock.h"
#include "Plugin.h"

namespace hb
{
	class Game
	{
	public:
		~Game();

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