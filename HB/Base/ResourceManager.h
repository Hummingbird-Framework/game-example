#ifndef HB_RESOURCE_MANAGER_H
#define HB_RESOURCE_MANAGER_H
#include <unordered_map>
#include <cassert>

namespace hb
{
	template <typename Resource, typename ResourceId, typename Hash = std::hash<ResourceId>>
	class ResourceManager
	{
	public:
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
			return m_info_table.find(id)->second.data;
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
			return m_info_table.find(id)->second.count;
		}
		// Returns total number of resources loaded
		int size() const
		{
			return m_id_table.size();
		}
		// Release all resources
		void clear()
		{
			m_resource_count = 0;
			m_id_table.clear();
			m_info_table.clear();
		}

	private:
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
#endif
