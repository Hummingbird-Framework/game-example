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
		  \brief Set the function that will be executed on the pre-update step.
		  \param pre_update Function to be executed.
		*/
		void setPreUpdateFunction(std::function<void(void)> pre_update);
		/*!
		  \brief Set the function that will be executed on the update step.
		  \param update Function to be executed.
		*/
		void setUpdateFunction(std::function<void(void)> update);
		/*!
		  \brief Set the function that will be executed on the post-update step.
		  \param post_update Function to be executed.
		*/
		void setPostUpdateFunction(std::function<void(void)> post_update);
		/*!
		  \brief Set the function that will be executed when the GameObject is destroyed.
		  \param destroy Function to be executed.
		*/
		void setDestroyFunction(std::function<void(void)> destroy);
		/*!
		  \brief Method called on the pre-update step.

		  Inside it calls the pre-update function defined.
		*/
		virtual void preUpdate() override;
		/*!
		  \brief Method called on the update step.

		  Inside it calls the update function defined.
		*/
		virtual void update() override;
		/*!
		  \brief Method called on the post-update step.

		  Inside it calls the post-update function defined.
		*/
		virtual void postUpdate() override;

	private:
		std::function<void(void)> m_pre_update;
		std::function<void(void)> m_update;
		std::function<void(void)> m_post_update;
		std::function<void(void)> m_destroy;
	};
}
#endif