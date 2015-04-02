#ifndef HB_RESOURCE_MANAGER_H
#define HB_RESOURCE_MANAGER_H
#include <unordered_map>
#include "Log.h"

namespace hb
{
	/*!
	  \class ResourceManager
	  \ingroup core
	  \brief Class for efficiently managing loaded resources.
	  \tparam ManagerType Type of the ResourceManager.
	  \tparam ResourceType Type of the resource being managed.
	  \tparam ResourceId Type of the unique id of the resource being managed.
	  \tparam Hash Hash method for the ResourceId.
	*/
	template <typename ManagerType, typename ResourceType, typename ResourceId, typename Hash = std::hash<ResourceId>>
	class ResourceManager
	{
	public:
		/*!
		  \brief Get the singleton instance.
		  \return __ManagerType__ singleton instance.
		*/
		static ManagerType* instance()
		{
			if (s_instance == nullptr)
				s_instance = new ManagerType();
			return s_instance;
		}
		/*!
		  \brief Class constructor
		*/
		ResourceManager()
		{
			m_resource_count = 0;
		}
		/*!
		  \brief Class destructor
		*/
		~ResourceManager(){}
		/*!
		  \brief Add resource to manager.
		  \param resource_id Unique id of the resource being added.
		  \param resource The resource being added.
		  \return ResourceManager identifier for the resource.

		  If a resource with the same _resource_id_ is already registered, its usage count will be incremented 
		  and the resource won't be stored again.
		*/
		int addResource(const ResourceId& resource_id, const ResourceType& resource)
		{
			int ret = -1;
			if (isLoaded(resource_id))
			{
				ret = m_id_table.find(resource_id)->second;
				m_info_table.find(ret)->second.count++;
			}
			else
			{
				ret = m_resource_count++;
				ResourceInfo ti;
				ti.id = ret;
				ti.count = 1;
				ti.it = m_id_table.insert(std::pair<ResourceId, int>(resource_id, ret)).first;
				ti.data = resource;
				m_info_table.insert(std::pair<int, ResourceInfo>(ret, ti));
			}
			hb_assert(m_id_table.size() == m_info_table.size(), "Resource management broke bad");
			return ret;
		}
		/*!
		  \brief Release a resource with identifier id.
		  \param id Identifier of the resource in the ResourceManager.

		  If there is registered more than one usage of the resource, its counter will be decresed 
		  and the resource won't be deleted until its usage count reaches 0.
		*/
		virtual void release(int id)
		{
			auto i = m_info_table.find(id);
			if (i == m_info_table.end())
				return;
			ResourceInfo& ti = i->second;
			if (--ti.count == 0)
			{
				m_id_table.erase(ti.it);
				m_info_table.erase(id);
			}
			hb_assert(m_id_table.size() == m_info_table.size(), "Resource management broke bad");
		}
		/*!
		  \brief Release all resources with identifier id.
		  \param id Identifier of the resource in the ResourceManager.

		  Removes the resource with identifier _id_, ignoring if it has more usages.
		*/
		void releaseAll(int id)
		{
			auto i = m_info_table.find(id);
			if (i == m_info_table.end())
				return;
			ResourceInfo& ti = i->second;
			m_id_table.erase(ti.it);
			m_info_table.erase(id);
			hb_assert(m_id_table.size() == m_info_table.size(), "Resource management broke bad");
		}
		/*!
		  \brief Get resource with identifier id.
		  \param id Identifier of the resource in the ResourceManager.
		  \return Constant reference to the resource.
		*/
		const ResourceType& get(int id) const
		{
			auto it = m_info_table.find(id);
			hb_assert(it != m_info_table.end(), "Resource with id " << id << "does not exist.");
			return it->second.data;
		}
		/*!
		  \brief Get resource with identifier id.
		  \param id Identifier of the resource in the ResourceManager.
		  \return Reference to the resource.
		*/
		ResourceType& get(int id)
		{
			auto it = m_info_table.find(id);
			hb_assert(it != m_info_table.end(), "Resource with id " << id << "does not exist.");
			return it->second.data;
		}
		/*!
		  \brief Get ResourceId of resource with identifier id 
		  \param id Identifier of the resource in the ResourceManager.
		  \return ResourceId of the resource with identifier _id_.
		*/
		const ResourceId& getId(int id) const
		{
			auto it = m_info_table.find(id);
			hb_assert(it != m_info_table.end(), "Resource with id " << id << "does not exist.");
			return it->second.it->first;
		}
		/*!
		  \brief Returns wether the resource with identifier id is loaded.
		  \param id Identifier of the resource in the ResourceManager.
		  \return Is resource with identifier _id_ loaded.
		*/
		bool isLoaded(int id) const
		{
			return (m_info_table.find(id) != m_info_table.end());
		}
		/*!
		  \brief Returns wether the resource with ResourceId _resource_id_ is loaded.
		  \param resource_id Unique id of the resource.
		  \return Is resource with ResourceId _resource_id_ loaded.
		*/
		bool isLoaded(const ResourceId& resource_id) const
		{
			return (m_id_table.find(resource_id) != m_id_table.end());
		}
		/*!
		  \brief Returns wether the resource with ResourceId _resource_id_ is loaded 
		  and if it is loaded, puts the ResourceManager id in _id_.
		  \param resource_id Unique id of the resource.
		  \return Is resource with ResourceId _resource_id_ loaded.
		*/
		bool isLoaded(const ResourceId& resource_id, int& id) const
		{
			auto it = m_id_table.find(resource_id);
			bool ret = (it != m_id_table.end());
			if (ret)
				id = it->second;
			return ret;
		}
		/*!
		  \brief Returns number of active requests for resource id.
		  \param id Identifier of the resource in the ResourceManager.
		  \return Usage count of the resource.
		*/
		int countResourceUsage(int id) const
		{
			int count = 0;
			auto it = m_info_table.find(id);
			if (it != m_info_table.end())
				count = it->second.count;
			return count;
		}
		/*!
		  \brief Returns number of resources currently loaded.
		  \return Number of resources currently loaded (Not counting usages).
		*/
		int size() const
		{
			return m_id_table.size();
		}
		/*!
		  \brief Returns number of all resources ever loaded.
		  \return Number of all resources ever loaded (Not counting usages).
		*/
		int resourceCount() const
		{
			return m_resource_count;
		}
		/*!
		  \brief Release all resources.
		*/
		void clear()
		{
			m_resource_count = 0;
			m_id_table.clear();
			m_info_table.clear();
		}

	private:
		static ManagerType* s_instance;
		struct ResourceInfo
		{
			int id, count;
			typename std::unordered_map<ResourceId, int, Hash>::iterator it;
			ResourceType data;
		};

		int m_resource_count;
		std::unordered_map<ResourceId, int, Hash> m_id_table;
		std::unordered_map<int, ResourceInfo> m_info_table;
	};
}
template <typename ManagerType, typename ResourceType, typename ResourceId, typename Hash>
ManagerType* hb::ResourceManager<ManagerType, ResourceType, ResourceId, Hash>::s_instance = nullptr;
#endif
