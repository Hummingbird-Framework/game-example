#ifndef HB_BOX2D_PLUGIN_H
#define HB_BOX2D_PLUGIN_H
#include "../Core/Plugin.h"
#include "Physics2d.h"

namespace hb
{
	class Box2DPlugin : public Plugin
	{
	public:
		Box2DPlugin();
		~Box2DPlugin();

		void preUpdate() override;
	
	private:
		Time m_time_left;
	};
}
#endif