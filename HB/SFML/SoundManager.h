#ifndef HB_SOUND_MANAGER
#define HB_SOUND_MANAGER
#include <string>
#include <SFML/Audio.hpp>
#include "../Base/ResourceManager.h"

namespace hb
{
	class SoundManager : public ResourceManager<sf::SoundBuffer, std::string>
	{
	public:
		static SoundManager* instance();
		int loadFromFile(const std::string& path);

	private:
		static SoundManager* s_instance;
	};
}
#endif