#include "Resource.h"
using namespace hb;

template <typename ResourceType, typename ResourceId, typename ResourceManager>
Resource<ResourceType, ResourceId, ResourceManager>::Resource(const ResourceType& resource, const ResourceId& id)
{
	ResourceManager::instance()->addResource(id, resource);
}


template <typename ResourceType, typename ResourceId, typename ResourceManager>
Resource<ResourceType, ResourceId, ResourceManager>::~Resource()
{

}


template <typename ResourceType, typename ResourceId, typename ResourceManager>
const ResourceType& Resource<ResourceType, ResourceId, ResourceManager>::get() const
{

}


template <typename ResourceType, typename ResourceId, typename ResourceManager>
const ResourceId& Resource<ResourceType, ResourceId, ResourceManager>::id() const
{

}