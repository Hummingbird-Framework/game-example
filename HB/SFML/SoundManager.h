#ifndef HB_SOUND_MANAGER
#define HB_SOUND_MANAGER
#include <string>
#include <SFML/Audio.hpp>
#include "../Core/ResourceManager.h"

namespace hb
{
	/**
	 * \class SoundManager
	 * \ingroup SFML
	 */
	class SoundManager : public ResourceManager<SoundManager, sf::SoundBuffer, std::string>
	{
	public:
		SoundManager();
	};
}
#endif