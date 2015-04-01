#ifndef HB_SPRITE_COMPONENT_H
#define HB_SPRITE_COMPONENT_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Renderer.h"
#include "../Core/GameObject.h"
#include "../Core/Transform.h"
#include "../Core/Time.h"
#include "Sprite.h"


namespace hb
{
	/**
	 * \class SpriteComponent
	 * \ingroup SFML-components
	 */
	class SpriteComponent : public GameObject::Component, public Transform
	{
	public:
		SpriteComponent(const Sprite& sprite = Sprite(), const std::vector<int>& frame_order = std::vector<int>(1, 0), const Time& frame_time = Time::seconds(0));
		virtual ~SpriteComponent() override;

		virtual void postUpdate() override;

		void setSprite(const Sprite& sprite);
		void setFrameOrder(const std::vector<int>& frame_order);
		const std::vector<int>& getFrameOrder() const;
		void setFrameTime(const Time& frame_time);
		const Time& getFrameTime() const;
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
		void setColor(const Color& color);
		const Color& getColor() const;

	protected:
		Vector2d getCoords();

		Time m_time_left, m_frame_time;
		unsigned int m_current_frame;
		bool m_visible;
		bool m_playing, m_looping;
		sf::Sprite m_sprite;
		Sprite m_animation;
		std::vector<int> m_frame_order;
		Color m_color;
	};
}
#endif