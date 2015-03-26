#ifndef HB_SOUND_COMPONENT_H
#define HB_SOUND_COMPONENT_H
#include <string>
#include <SFML/Audio.hpp>
#include "../Core/GameObject.h"
#include "../Core/Transform.h"
#include "SoundManager.h"
#include "SoundBuffer.h"

namespace hb
{
	/**
	 * \class SoundComponent
	 * \ingroup SFML-components
	 */
	class SoundComponent : public GameObject::Component, public Transform
	{
	public:
		enum Status
		{
			Stopped,
			Paused,
			Playing
		};

		SoundComponent();
		SoundComponent(const SoundBuffer& buffer);
		virtual ~SoundComponent() override;

		static GameObject::Component* factory(std::map<std::string, std::string>& properties, int i);
		static const std::string& getFootprint();

		void update() override;

		void setBuffer(const SoundBuffer& buffer);
		SoundBuffer& getBuffer();
		const SoundBuffer& getBuffer() const;
		void play();
		void pause();
		void stop();
		Status getStatus() const;
		Time getPlayingOffset() const;
		void setPlayingOffset(const Time& offset);
		void loop(bool loop);
		bool isLooping() const;
		void setPitch(double pitch);
		double getPitch() const;
		void setVolume(double volume);
		double getVolume() const;
		void setRelativeToListener(bool relative);
		bool isRelativeToListener() const;
		void setMinDistance(double distance);
		double getMinDistance() const;
		void setAttenuation(double attenuation);
		double getAttenuation() const;

	private:
		static std::string s_footprint;
		sf::Sound m_sound;
		SoundBuffer m_buffer;
	};
}
#endif