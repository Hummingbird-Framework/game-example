#ifndef HB_PLUGIN_H
#define HB_PLUGIN_H
#include <string>
#include <map>
#include "GameObject.h"

namespace hb
{
	/*!
	  \class Plugin
	  \ingroup core
	*/
	class Plugin
	{
	public:
		Plugin(){};
		virtual ~Plugin(){};

		typedef GameObject::Component* (*ComponentFactory)(std::map<std::string, std::string>&, int);
		virtual std::map<std::string, ComponentFactory> getComponentFactory() const
		{return std::map<std::string, ComponentFactory>();};
		virtual void gameStart(){};
		virtual void preUpdate(){};
		virtual void postUpdate(){};
		virtual void gameEnd(){};
		
	};
}
#endif
