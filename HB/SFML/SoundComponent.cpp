#include "SoundComponent.h"
using namespace hb;


SoundComponent::SoundComponent():
GameObject::Component(),
m_sound_id(-1)
{

}


SoundComponent::~SoundComponent()
{
	SoundManager::instance()->release(m_sound_id);
}


void SoundComponent::setSound(const std::string& sound_path)
{
	int m_sound_id = SoundManager::instance()->loadFromFile(sound_path);
	m_sound.setBuffer(SoundManager::instance()->get(m_sound_id));
}


sf::Sound& SoundComponent::getSound()
{
	return m_sound;
}


const sf::Sound& SoundComponent::getSound() const
{
	return m_sound;
}


void SoundComponent::update()
{
	float x = getPosition().x + getGameObject()->getPosition().x;
	float y = getPosition().y + getGameObject()->getPosition().y;
	float z = getPosition().z + getGameObject()->getPosition().z;
	m_sound.setPosition(x, y, z);
}
