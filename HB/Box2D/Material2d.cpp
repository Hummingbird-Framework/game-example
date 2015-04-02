#include "Material2d.h"
using namespace hb;


Material2d::Material2d(const Material2dDef& material, const std::string& name):
Resource<Material2dDef, std::string, Material2dManager>(material, name)
{

}


Material2d::Material2d(const std::string& name):
Resource<Material2dDef, std::string, Material2dManager>(name)
{

}


double Material2d::getFriction() const
{
	return Material2dManager::instance()->get(m_id).friction;
}


double Material2d::getBounciness() const
{
	return Material2dManager::instance()->get(m_id).bounciness;
}


void Material2d::setFriction(double friction)
{
	Material2dManager::instance()->get(m_id).friction = friction;
}


void Material2d::setBounciness(double bounciness)
{
	Material2dManager::instance()->get(m_id).bounciness = bounciness;
}
