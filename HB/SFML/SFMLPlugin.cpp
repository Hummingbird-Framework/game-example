#include "SFMLPlugin.h"
using namespace hb;

SFMLPlugin::SFMLPlugin()
{}


SFMLPlugin::~SFMLPlugin()
{}


std::map<std::string, Plugin::ComponentFactory> SFMLPlugin::getComponentFactory() const
{
	std::map<std::string, ComponentFactory> list;
	list[SpriteComponent::getFootprint()] = SpriteComponent::factory;
	list[SoundComponent::getFootprint()] = SoundComponent::factory;
	list[CollisionComponent::getFootprint()] = CollisionComponent::factory;
	list[ClickableComponent::getFootprint()] = ClickableComponent::factory;
	return list;
}


void SFMLPlugin::preUpdate()
{
	InputManager::instance()->update();
}


void SFMLPlugin::postUpdate()
{
	hb::Renderer::draw();
}
