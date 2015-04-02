#ifndef HB_RESOURCE_H
#define HB_RESOURCE_H


namespace hb
{
	/*!
	  \class Resource
	  \ingroup core
	  \brief Class representing a loaded resource.
	  \tparam ResourceType Type of the resource loaded.
	  \tparam ResourceId Type that uniquely identifies a ResourceType
	  \tparam ResourceManager Manager of the Resource. It must inherit from ResourceManager.
	*/
	template <typename ResourceType, typename ResourceId, typename ResourceManager>
	class Resource
	{
	public:
		/*!
		  \brief Class constructor.
		  \param resource ResourceType instance to manage.
		  \param id Unique id of the resource.

		  Adds the resource to its ResourceManager.
		*/
		Resource(const ResourceType& resource, const ResourceId& id)
		{
			m_id = ResourceManager::instance()->addResource(id, resource);
		}
		/*!
		  \brief Class constructor. Used for getting an already loaded resource.
		  \param id Unique id of the resource.

		  Loads a resource from the ResourceManager. If the resource with Unique id 
		  _id_ hasn't been loaded yet, it will register ResourceType instance using the 
		  default constructor.
		*/
		Resource(const ResourceId& id)
		{
			if (not ResourceManager::instance()->isLoaded(id, m_id))
				m_id = ResourceManager::instance()->addResource(id, ResourceType());
		}
		/*!
		  \brief Copy constructor.
		  \param other Original instance.
		*/
		Resource(const Resource& other)
		{
			m_id = ResourceManager::instance()->addResource(other.id(), other.get());
		}
		/*!
		  \brief Copy assignment.
		  \param other Original instance.
		*/
		Resource& operator=(const Resource& other)
		{
			m_id = ResourceManager::instance()->addResource(other.id(), other.get());
			return *this;
		}
		/*!
		  \brief Class destructor.

		  Removes the resource from its ResourceManager.
		*/
		~Resource()
		{
			ResourceManager::instance()->release(m_id);
		}

		/*!
		  \brief Get the resource.
		  \return Constant reference to the resource.
		*/
		const ResourceType& get() const
		{
			return ResourceManager::instance()->get(m_id);
		}
		/*!
		  \brief Get the resource.
		  \return Reference to the resource.
		*/
		ResourceType& get()
		{
			return ResourceManager::instance()->get(m_id);
		}
		/*!
		  \brief Get the resource id.
		*/
		const ResourceId& id() const
		{
			return ResourceManager::instance()->getId(m_id);
		}
	
	protected:
		int m_id;
	};
}
#endif