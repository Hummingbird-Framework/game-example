#ifndef HB_DATA_COMPONENT_H
#define HB_DATA_COMPONENT_H
#include "GameObject.h"

namespace hb
{
	/*!
	  \class DataComponent
	  \ingroup core-components
	  \brief A GameObject::Component for storing an instance of T into a GameObject.
	*/
	template <typename T>
	class DataComponent : public GameObject::Component
	{
	public:
		/*!
		  \brief Class default constructor.
		*/
		DataComponent():
		Component()
		{}
		/*!
		  \brief Class constructor.
		  \param data T instance to store in the component

		  Makes a copy of data and stores it.
		*/
		DataComponent(const T& data):
		Component()
		{
			m_data = data;
		}
		/*!
		  \brief Class destructor
		*/
		virtual ~DataComponent() override
		{}
		/*!
		  \brief Data setter.
		  \param data T instance to store in the component

		  Makes a copy of data and stores it.
		*/
		void setData(const T& data)
		{
			m_data = data;
		}
		/*!
		  \brief Data getter.

		  \return Reference to stored T instance
		*/
		T& getData()
		{
			return m_data;
		}
		/*!
		  \brief Data getter.

		  \return Constant reference to stored T instance
		*/
		const T& getData() const
		{
			return m_data;
		}

	private:
		T m_data;
	};

	/*!
	  \class DataComponent<T*>
	  \ingroup core-components
	  \brief (Class template specialization) A GameObject::Component for storing a pointer to an instance of T into a GameObject.
	*/
	template<class T>
	class DataComponent<T*> : public GameObject::Component
	{
	public:
		/*!
		  \brief Class default constructor.
		*/
		DataComponent():
		Component()
		{
			m_data = new T();
		}
		/*!
		  \brief Class constructor.
		  \param data Pointer to T instance to store in the component

		  Makes a copy of data and stores it.
		*/
		DataComponent(T* data):
		Component()
		{
			m_data = data;
		}
		/*!
		  \brief Class destructor

		  Calls the destructor of the pointed T instance (delete)
		*/
		virtual ~DataComponent() override
		{
			delete m_data;
		}
		/*!
		  \brief Data setter.
		  \param data Pointer to T instance to store in the component

		  Makes a copy of data and stores it.
		*/
		void setData(T* data)
		{
			m_data = data;
		}
		/*!
		  \brief Data getter
		  \return Stored T pointer
		*/
		T* getData()
		{
			return m_data;
		}
		/*!
		  \brief Data getter
		  \return Stored T constant pointer
		*/
		const T* getData() const
		{
			return m_data;
		}

	private:
		T* m_data;
	};
}
#endif