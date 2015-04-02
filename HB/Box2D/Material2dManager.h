#ifndef HB_MATERIAL_2D_MANAGER_H
#define HB_MATERIAL_2D_MANAGER_H
#include "../Core/ResourceManager.h"
#include "Material2dDef.h"


namespace hb
{
	class Material2dManager : public ResourceManager<Material2dManager, Material2dDef, std::string>
	{
	public:
		Material2dManager();
	};
}
#endif