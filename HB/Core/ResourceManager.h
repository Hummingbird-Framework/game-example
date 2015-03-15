#ifndef HB_RESOURCE_MANAGER_H
#define HB_RESOURCE_MANAGER_H
#include <unordered_map>
#include <cassert>

namespace hb
{
	template <typename ManagerType, typename Resource, typename ResourceId, typename Hash = std::hash<ResourceId>>
	class ResourceManager
	{
	public:

		static ManagerType* instance()
		{
			if (s_instance == nullptr)
				s_instance = new ManagerType();
			return s_instance;
		}
		// Constructor
		ResourceManager()
		{
			m_resource_count = 0;
		}
		// Destructor
		~ResourceManager(){}
		// Add Resource to manager
		int addResource(const ResourceId& resource_id, const Resource& resource)
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
			assert(m_id_table.size() == m_info_table.size());
			return ret;
		}
		// Release a Resource resource with identifier id
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
			assert(m_id_table.size() == m_info_table.size());
		}
		// Release all Resource resources with identifier id
		void releaseAll(int id)
		{
			auto i = m_info_table.find(id);
			if (i == m_info_table.end())
				return;
			ResourceInfo& ti = i->second;
			m_id_table.erase(ti.it);
			m_info_table.erase(id);
			assert(m_id_table.size() == m_info_table.size());
		}
		// Get Resource with identifier id
		const Resource& get(int id) const
		{
			auto it = m_info_table.find(id);
			assert(it != m_info_table.end());
			return it->second.data;
		}
		// Get Resource with identifier id
		Resource& get(int id)
		{
			auto it = m_info_table.find(id);
			assert(it != m_info_table.end());
			return it->second.data;
		}
		// Get ResourceId of resource with identifier id 
		const ResourceId& getId(int id) const
		{
			auto it = m_info_table.find(id);
			assert(it != m_info_table.end());
			return it->second.it->first;
		}
		// Returns wether the Resource resource with identifier id is loaded
		bool isLoaded(int id) const
		{
			return (m_info_table.find(id) != m_info_table.end());
		}
		// Returns wether the Resource resource with ResourceId resource_id is loaded
		bool isLoaded(const ResourceId& resource_id) const
		{
			return (m_id_table.find(resource_id) != m_id_table.end());
		}
		// Returns number of active requests for resource id
		int countResourceUsage(int id) const
		{
			int count = 0;
			auto it = m_info_table.find(id);
			if (it != m_info_table.end())
				count = it->second.count;
			return count;
		}
		// Returns number of resources currently loaded
		int size() const
		{
			return m_id_table.size();
		}
		// Returns number of all resources ever loaded
		int resourceCount() const
		{
			return m_resource_count;
		}
		// Release all resources
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
			Resource data;
		};

		int m_resource_count;
		std::unordered_map<ResourceId, int, Hash> m_id_table;
		std::unordered_map<int, ResourceInfo> m_info_table;
	};
}
template <typename ManagerType, typename Resource, typename ResourceId, typename Hash>
ManagerType* hb::ResourceManager<ManagerType, Resource, ResourceId, Hash>::s_instance = nullptr;
#endif
