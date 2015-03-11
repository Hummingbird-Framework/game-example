#ifndef HB_SPRITE_COMPONENT_H
#define HB_SPRITE_COMPONENT_H
#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include "../Base/GameObject.h"
#include "../Base/Transform.h"
#include "../Base/Time.h"
#include "Sprite.h"


namespace hb
{
	class SpriteComponent : public GameObject::Component, public Transform
	{
	public:
		SpriteComponent(const Sprite& sprite = Sprite());
		virtual ~SpriteComponent() override;
		void setSprite(const Sprite& sprite);
		const Sprite& getSprite() const;
		Sprite& getSprite();
		Vector2d getSize() const;
		bool isVisible() const;
		void setVisible(bool visible);
		bool isLooping() const;
		void loop(bool loop);
		bool isPlaying() const;
		void play();
		void stop();
		virtual void postUpdate() override;

	protected:
		Vector2d getCoords();

		Time m_time_left;
		int m_current_frame;
		bool m_visible;
		bool m_playing, m_looping;
		sf::Sprite m_sprite;
		Sprite m_animation;
	};
}
#endif