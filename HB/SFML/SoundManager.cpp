#include "SoundManager.h"
using namespace hb;


SoundManager::SoundManager():
ResourceManager<SoundManager, sf::SoundBuffer, std::string>()
{}
