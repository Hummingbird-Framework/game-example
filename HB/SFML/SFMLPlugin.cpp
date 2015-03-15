#include "SFMLPlugin.h"
using namespace hb;

SFMLPlugin::SFMLPlugin()
{}


SFMLPlugin::~SFMLPlugin()
{}


void SFMLPlugin::preUpdate()
{
	InputManager::instance()->update();
}


void SFMLPlugin::postUpdate()
{
	hb::Renderer::draw();
}
