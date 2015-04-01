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
	  \brief Base class for implementing custom Plugin%s.
	*/
	class Plugin
	{
	public:
		/*!
		  \brief Class constructor.
		*/
		Plugin(){};
		/*!
		  \brief Class destructor.
		*/
		virtual ~Plugin(){};

		/*!
		  \brief Function executed just before entering the gameloop.
		*/
		virtual void gameStart(){};
		/*!
		  \brief Function executed before updating the GameObject%s.
		*/
		virtual void preUpdate(){};
		/*!
		  \brief Function executed after updating the GameObject%s.
		*/
		virtual void postUpdate(){};
		/*!
		  \brief Function executed after exiting the gameloop.
		*/
		virtual void gameEnd(){};
		
	};
}
#endif
