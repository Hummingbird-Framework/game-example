#include "SoundComponent.h"
using namespace hb;

std::string SoundComponent::s_footprint = "Sound";

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


GameObject::Component* SoundComponent::factory(std::map<std::string, std::string>& properties, int i)
{
	std::string path = properties[s_footprint + "[" + std::to_string(i) + "].path"];
	hb::SoundBuffer sound_buffer = hb::SoundBuffer::loadFromFile(path);

	SoundComponent* c = new SoundComponent(sound_buffer);

	std::string playingOffset = properties[s_footprint + "[" + std::to_string(i) + "].playingOffset"];
	if (playingOffset.length() != 0)
		c->setPlayingOffset(Time::milliseconds(atoi(playingOffset.c_str())));

	std::string pitch = properties[s_footprint + "[" + std::to_string(i) + "].pitch"];
	if (pitch.length() != 0)
		c->setPitch(strtod(pitch.c_str(), NULL));

	std::string volume = properties[s_footprint + "[" + std::to_string(i) + "].volume"];
	if (volume.length() != 0)
		c->setVolume(strtod(volume.c_str(), NULL));

	std::string relativeToListener = properties[s_footprint + "[" + std::to_string(i) + "].relativeToListener"];
	if (relativeToListener.length() != 0)
		c->setRelativeToListener(relativeToListener == "true");

	std::string minDistance = properties[s_footprint + "[" + std::to_string(i) + "].minDistance"];
	if (minDistance.length() != 0)
		c->setMinDistance(strtod(minDistance.c_str(), NULL));

	std::string attenuation = properties[s_footprint + "[" + std::to_string(i) + "].attenuation"];
	if (attenuation.length() != 0)
		c->setAttenuation(strtod(attenuation.c_str(), NULL));

	std::string loop = properties[s_footprint + "[" + std::to_string(i) + "].loop"];
	if (loop.length() != 0)
		c->loop(loop == "true");

	std::string status = properties[s_footprint + "[" + std::to_string(i) + "].status"];
	if (status.length() != 0)
	{
		if (status == "Stopped")
		{
			c->stop();
		}
		if (status == "Paused")
		{
			c->pause();
		}
		if (status == "Playing")
		{
			c->play();
		}
	}

	return c;
}


const std::string& SoundComponent::getFootprint()
{
	return s_footprint;
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
