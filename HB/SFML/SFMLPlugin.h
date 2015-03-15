#ifndef HB_SFML_PLUGIN_H
#define HB_SFML_PLUGIN_H
#include "../Core/Plugin.h"
#include "InputManager.h"
#include "Renderer.h"

namespace hb
{
	class SFMLPlugin : public Plugin
	{
	public:
		SFMLPlugin();
		virtual ~SFMLPlugin() override;

		virtual void preUpdate() override;
		virtual void postUpdate() override;
		
	};
}
#endif