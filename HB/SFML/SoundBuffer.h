#ifndef HB_SOUND_BUFFER_H
#define HB_SOUND_BUFFER_H
#include "../Core/Resource.h"
#include "../Core/Time.h"
#include "SoundManager.h"

namespace hb
{
	/**
	 * \class SoundBuffer
	 * \ingroup SFML
	 */
	class SoundBuffer : public Resource<sf::SoundBuffer, std::string, SoundManager>
	{
	public:
		SoundBuffer(const sf::SoundBuffer& buffer, const std::string& id);
		SoundBuffer(const std::string& id);
		SoundBuffer():SoundBuffer(sf::SoundBuffer(), ""){}
		~SoundBuffer();
		static SoundBuffer loadFromFile(const std::string& path);
		Time getDuration() const;
	};
}
#endif