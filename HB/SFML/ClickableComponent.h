#ifndef HB_CLICKABLE_COMPONENT_H
#define HB_CLICKABLE_COMPONENT_H
#include <functional>
#include "../Core/GameObject.h"
#include "InputManager.h"

namespace hb
{
	/**
	 * \class ClickableComponent
	 * \ingroup SFML-components
	 */
	class ClickableComponent : public GameObject::Component, public Transform
	{
	public:
		ClickableComponent();
		ClickableComponent(const Vector2d& size);
		~ClickableComponent();
		void setOnClick(std::function<void(void)>&& onClick);
		void setSize(const Vector2d& size);
		const Vector2d& getSize() const;

	private:
		Vector2d m_size;
		std::function<void(void)> m_onClick;
		hb::InputManager::ListenerId<hb::MouseButtonWorld> m_listener_id;
	};
}
#endif