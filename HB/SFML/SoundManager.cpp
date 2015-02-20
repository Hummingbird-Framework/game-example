#include "SoundManager.h"
using namespace hb;

SoundManager* SoundManager::s_instance = NULL;

SoundManager* SoundManager::instance()
{
	if (s_instance == NULL)
		s_instance = new SoundManager();

	return s_instance;
}

int SoundManager::loadFromFile(const std::string& path)
{
	sf::SoundBuffer sb;
	if (!isLoaded(path))
		sb.loadFromFile(path);

	return this->addResource(path, sb);
}
