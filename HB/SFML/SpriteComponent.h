#ifndef HB_SPRITE_COMPONENT_H
#define HB_SPRITE_COMPONENT_H
#include <SFML/Graphics.hpp>
#include "RenderWindowManager.h"
#include "../Base/GameObject.h"
#include "../Base/Transform.h"
#include "../Base/Time.h"
#include "../Base/Vector2d.h"
#include "TextureManager.h"

namespace hb
{
	class SpriteComponent : public GameObject::Component, public Transform
	{
	public:
		class Animation
		{
		public:
			friend class SpriteComponent;

			Animation(const std::string& path = "t404", const sf::IntRect& area = sf::IntRect(), const Vector2d& frame_size = Vector2d(64, 64), const Vector2d& frame_margin = Vector2d(0, 0), int begin_frame = 0, int end_frame = 0, const Time& frame_time = Time::seconds(1));
			Animation(const Animation& other);
			Animation& operator=(const Animation& other);
			~Animation();
			void setTexture(const std::string& path, const sf::IntRect& area = sf::IntRect());
			void setFrameTime(const Time& frame_time);
			void setFrameInterval(int begin_frame, int end_frame);
			void setFrameSize(const Vector2d& frame_size);
			void setFrameMargin(const Vector2d& frame_margin);

		private:
			std::string m_path;
			sf::IntRect m_area;
			Time m_time_left;
			Time m_frame_time;
			Vector2d m_frame_size;
			Vector2d m_frame_margin;
			int m_begin_frame, m_current_frame, m_end_frame, m_texture_id;
		};

		SpriteComponent(RenderWindowManager* render_manager, const Animation& animation = Animation());
		virtual ~SpriteComponent() override;
		void setRenderWindowManager(RenderWindowManager* render_manager);
		RenderWindowManager* getRenderWindowManager();
		const RenderWindowManager* getRenderWindowManager() const;
		void setAnimation(const Animation& animation);
		const Animation& getAnimation() const;
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
		Animation m_animation;
		RenderWindowManager* m_render_manager;
	};
}
#endif