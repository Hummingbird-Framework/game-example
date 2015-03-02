#include "SoundManager.h"
using namespace hb;


SoundManager::SoundManager():
ResourceManager<SoundManager, sf::SoundBuffer, std::string>()
{}


int SoundManager::loadFromFile(const std::string& path)
{
	sf::SoundBuffer sb;
	if (!isLoaded(path))
		sb.loadFromFile(path);

	return this->addResource(path, sb);
}
