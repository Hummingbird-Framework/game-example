#include "SoundComponent.h"
using namespace hb;


SoundComponent::SoundComponent():
GameObject::Component(),
m_buffer(SoundBuffer(sf::SoundBuffer(), ""))
{

}

SoundComponent::SoundComponent(const SoundBuffer& buffer):
GameObject::Component()
{
	m_buffer = buffer;
	m_sound.setBuffer(buffer.get());
}

SoundComponent::~SoundComponent()
{

}


SoundBuffer& SoundComponent::getBuffer()
{
	return m_buffer;
}


const SoundBuffer& SoundComponent::getBuffer() const
{
	return m_buffer;
}


void SoundComponent::update()
{
	float x = getPosition().x + getGameObject()->getPosition().x;
	float y = getPosition().y + getGameObject()->getPosition().y;
	float z = getPosition().z + getGameObject()->getPosition().z;
	m_sound.setPosition(x, y, z);
}


void SoundComponent::play()
{
	m_sound.play();
}


void SoundComponent::pause()
{
	m_sound.pause();
}


void SoundComponent::stop()
{
	m_sound.stop();
}


SoundComponent::Status SoundComponent::getStatus() const
{
	sf::SoundSource::Status s = m_sound.getStatus();
	Status ret;
	switch(s)
	{
		case sf::SoundSource::Status::Playing:
			ret = Status::Playing;
			break;
		case sf::SoundSource::Status::Paused:
			ret = Status::Paused;
			break;
		default:
			ret = Status::Stopped;
	}
	return ret;
}


Time SoundComponent::getPlayingOffset() const
{
	return Time::microseconds(m_sound.getPlayingOffset().asMicroseconds());
}


void SoundComponent::setPlayingOffset(const Time& offset)
{
	m_sound.setPlayingOffset(sf::microseconds(offset.asMicroseconds()));
}


void SoundComponent::loop(bool loop)
{
	m_sound.setLoop(loop);
}


bool SoundComponent::isLooping() const
{
	return m_sound.getLoop();
}


void SoundComponent::setPitch(double pitch)
{
	m_sound.setPitch(pitch);
}


double SoundComponent::getPitch() const
{
	return m_sound.getPitch();
}


void SoundComponent::setVolume(double volume)
{
	m_sound.setVolume(volume);
}


double SoundComponent::getVolume() const
{
	return m_sound.getVolume();
}


void SoundComponent::setRelativeToListener(bool relative)
{
	m_sound.setRelativeToListener(relative);
}


bool SoundComponent::isRelativeToListener() const
{
	return m_sound.isRelativeToListener();
}


void SoundComponent::setMinDistance(double distance)
{
	m_sound.setMinDistance(distance);
}


double SoundComponent::getMinDistance() const
{
	return m_sound.getMinDistance();
}


void SoundComponent::setAttenuation(double attenuation)
{
	m_sound.setAttenuation(attenuation);
}


double SoundComponent::getAttenuation() const
{
	return m_sound.getAttenuation();
}
