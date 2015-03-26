#ifndef HB_RESOURCE_H
#define HB_RESOURCE_H


namespace hb
{
	/*!
	  \class Resource
	  \ingroup core
	*/
	template <typename ResourceType, typename ResourceId, typename ResourceManager>
	class Resource
	{
	public:
		Resource(const ResourceType& resource, const ResourceId& id)
		{
			m_id = ResourceManager::instance()->addResource(id, resource);
		}
		Resource(const Resource& other)
		{
			m_id = ResourceManager::instance()->addResource(other.id(), other.get());
		}
		Resource& operator=(const Resource& other)
		{
			m_id = ResourceManager::instance()->addResource(other.id(), other.get());
			return *this;
		}
		~Resource()
		{
			ResourceManager::instance()->release(m_id);
		}

		const ResourceType& get() const
		{
			return ResourceManager::instance()->get(m_id);
		}
		ResourceType& get()
		{
			return ResourceManager::instance()->get(m_id);
		}
		const ResourceId& id() const
		{
			return ResourceManager::instance()->getId(m_id);
		}
	
	protected:
		int m_id;
	};
}
#endif