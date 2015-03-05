#ifndef HB_FUNCTION_COMPONENT_H
#define HB_FUNCTION_COMPONENT_H
#include <functional>
#include "GameObject.h"
#include "DataRepository.h"

namespace hb
{
	class FunctionComponent : public GameObject::Component, public hb::DataRepository
	{
	public:
		FunctionComponent();
		virtual ~FunctionComponent() override;
		void setPreUpdateFunction(std::function<void(void)> pre_update);
		void setUpdateFunction(std::function<void(void)> update);
		void setPostUpdateFunction(std::function<void(void)> post_update);
		void setDestroyFunction(std::function<void(void)> destroy);
		void run(std::function<void(void)> method);
		virtual void preUpdate() override;
		virtual void update() override;
		virtual void postUpdate() override;

	private:
		std::function<void(void)> m_pre_update;
		std::function<void(void)> m_update;
		std::function<void(void)> m_post_update;
		std::function<void(void)> m_destroy;
	};
}
#endif