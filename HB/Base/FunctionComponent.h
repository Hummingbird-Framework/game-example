#ifndef HB_FUNCTION_COMPONENT_H
#define HB_FUNCTION_COMPONENT_H
#include <functional>
#include "GameObject.h"

namespace hb
{
	class FunctionComponent : public GameObject::Component
	{
	public:
		FunctionComponent();
		void setPreUpdateFunction(std::function<void(GameObject*)> pre_update);
		void setUpdateFunction(std::function<void(GameObject*)> update);
		void setPostUpdateFunction(std::function<void(GameObject*)> post_update);
		virtual void preUpdate() override;
		virtual void update() override;
		virtual void postUpdate() override;

	private:
		std::function<void(GameObject*)> m_pre_update;
		std::function<void(GameObject*)> m_update;
		std::function<void(GameObject*)> m_post_update;
	};
}
#endif