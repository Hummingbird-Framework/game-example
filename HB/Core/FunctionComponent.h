#ifndef HB_FUNCTION_COMPONENT_H
#define HB_FUNCTION_COMPONENT_H
#include <functional>
#include "GameObject.h"
#include "DataRepository.h"

namespace hb
{
	/*!
	  \class FunctionComponent
	  \brief GameObject::Component with parametrized update function.
	  \ingroup core-components

	  This class allows you to set the functions that must be executed on 
	  __pre-update__, __update__, __post-update__ and __destruction__ of a GameObject.
	*/
	class FunctionComponent : public GameObject::Component
	{
	public:
		/*!
		  \brief Class constructor.
		  
		  All functions are initialized as no-op.
		*/
		FunctionComponent();
		/*!
		  \brief Class destructor.

		  The function set for destroy is called here.
		*/
		virtual ~FunctionComponent() override;

		/*!
		  \brief Add listener to GameObject MessageManager.
		*/
		void addListener(const std::string& name, std::function<void(DataRepository&)>&& listener);

	private:
		std::vector<GameObjectMessageManager::ListenerId<DataRepository>> m_vector_of_listener_id;
	};
}
#endif