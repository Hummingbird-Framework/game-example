#ifndef HB_MATERIAL_2D_H
#define HB_MATERIAL_2D_H
#include <string>
#include "../Core/Resource.h"
#include "Material2dManager.h"


namespace hb
{
	class Material2d : public Resource<Material2dDef, std::string, Material2dManager>
	{
	public:
		Material2d(const Material2dDef& material, const std::string& name);
		Material2d(const std::string& name);

		double getFriction() const;
		double getBounciness() const;

		void setFriction(double friction);
		void setBounciness(double bounciness);
	};
}
#endif