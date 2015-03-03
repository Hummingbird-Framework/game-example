#ifndef HB_SOUND_COMPONENT_H
#define HB_SOUND_COMPONENT_H
#include <string>
#include <SFML/Audio.hpp>
#include "../Base/GameObject.h"
#include "../Base/Transform.h"
#include "SoundManager.h"

// TODO: Make SoundComponent equivalent of SpriteComponent (Sprite)

namespace hb
{
	class SoundComponent : public GameObject::Component, public Transform
	{
	public:
		SoundComponent();
		virtual ~SoundComponent() override;
		void setSound(const std::string& sound_path);
		sf::Sound& getSound();
		const sf::Sound& getSound() const;
		void update() override;

	private:
		sf::Sound m_sound;
		int m_sound_id;
	};
}
#endif