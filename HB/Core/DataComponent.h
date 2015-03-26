#ifndef HB_DATA_COMPONENT_H
#define HB_DATA_COMPONENT_H
#include "GameObject.h"

namespace hb
{
	/*!
	  \class DataComponent
	  \ingroup core-components
	*/
	template <typename T>
	class DataComponent : public GameObject::Component
	{
	public:
		DataComponent():
		Component()
		{}
		virtual ~DataComponent() override
		{}
		DataComponent(const T& data):
		Component()
		{
			m_data = data;
		}
		void setData(const T& data)
		{
			m_data = data;
		}
		T& getData()
		{
			return m_data;
		}
		const T& getData() const
		{
			return m_data;
		}

	private:
		T m_data;
	};
}
#endif