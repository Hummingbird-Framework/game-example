#ifndef HB_LISTENER_COMPONENT_H
#define HB_LISTENER_COMPONENT_H
#include <SFML/Audio.hpp>
#include "../Core/GameObject.h"


namespace hb
{
	/**
	 * \class ListenerComponent
	 * \ingroup SFML-components
	 */
	class ListenerComponent : public GameObject::Component
	{
	public:
		ListenerComponent();
		~ListenerComponent();
		void init() override;
		void postUpdate() override;
		void setDirection(const Vector3d& direction) const;
	};
}
#endif