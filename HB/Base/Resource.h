#ifndef HB_RESOURCE_H
#define HB_RESOURCE_H

// TODO: Terminar Resource y ResourceManager

namespace hb
{
	template <typename ResourceType, typename ResourceId, typename ResourceManager>
	class Resource
	{
	public:
		Resource(const ResourceType& resource, const ResourceId& id);
		~Resource();
		const ResourceType& get() const;
		const ResourceId& id() const;
	
	private:
		int m_id;
	};
}
#endif