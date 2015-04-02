#include "SoundBuffer.h"
using namespace hb;


SoundBuffer::SoundBuffer(const sf::SoundBuffer& buffer, const std::string& id):
Resource<sf::SoundBuffer, std::string, SoundManager>(buffer, id)
{

}


SoundBuffer::SoundBuffer(const std::string& id):
Resource<sf::SoundBuffer, std::string, SoundManager>(id)
{

}


SoundBuffer::~SoundBuffer()
{

}


SoundBuffer SoundBuffer::loadFromFile(const std::string& path)
{
	auto SM = SoundManager::instance();
	sf::SoundBuffer sb;
	if (!SM->isLoaded(path))
		sb.loadFromFile(path);

	return SoundBuffer(sb, path);
}


Time SoundBuffer::getDuration() const
{
	return Time::microseconds(SoundManager::instance()->get(m_id).getDuration().asMicroseconds());
}
