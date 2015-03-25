#ifndef HB_TMX_SCENE_H
#define HB_TMX_SCENE_H
#include <sstream>
#include <tmxparser/Tmx.h>
#include "TmxObjectTypeFactory.h"
#include "../Core/Game.h"
#include "../SFML.h"

namespace hb
{
	class TmxScene : public Game::Scene
	{
	public:
		TmxScene(const std::string& file_name);
		~TmxScene();

	private:
		std::string m_filename;
	};
}
#endif