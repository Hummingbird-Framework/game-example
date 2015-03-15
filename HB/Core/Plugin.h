#ifndef HB_PLUGIN_H
#define HB_PLUGIN_H

namespace hb
{
	class Plugin
	{
	public:
		Plugin(){};
		virtual ~Plugin(){};

		virtual void gameStart(){};
		virtual void preUpdate(){};
		virtual void postUpdate(){};
		virtual void gameEnd(){};
		
	};
}
#endif