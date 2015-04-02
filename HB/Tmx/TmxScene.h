#ifndef HB_TMX_SCENE_H
#define HB_TMX_SCENE_H
#include <sstream>
#include <tmxparser/Tmx.h>
#include "TmxObjectTypeFactory.h"
#include "../Core/Game.h"
#include "../SFML.h"
#include "TmxVersion.h"

namespace hb
{
	/**
	 * \class TmxScene
	 * \ingroup tmx
	 */
	class TmxScene : public Game::Scene
	{
	public:
		TmxScene(const std::string& scene_name, const std::string& file_name, std::function<void(const Tmx::Map*)>& post_init);
		TmxScene(const std::string& scene_name, const std::string& file_name, std::function<void(const Tmx::Map*)>&& post_init = std::move([](const Tmx::Map*){}));
		~TmxScene();

	private:
		std::string m_filename;
		std::function<void(const Tmx::Map*)> m_post_init;
	};
}
#endif