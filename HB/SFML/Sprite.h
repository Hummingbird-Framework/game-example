#ifndef HB_SPRITE_H
#define HB_SPRITE_H
#include <utility>
#include <vector>
#include "../Base/Time.h"
#include "../Base/Vector2d.h"
#include "Texture.h"

namespace hb
{
	class Sprite
	{
	public:
		friend class SpriteComponent;
		Sprite(const Texture& texture = Texture::t404(), const Vector2d& frame_size = Vector2d(64, 64), const Vector2d& frame_margin = Vector2d(0, 0), const std::vector<int>& frame_order = {0}, const Time& frame_time = Time::seconds(0));
		Sprite(const Texture& texture, const Vector2d& frame_size, const Vector2d& frame_margin, int begin_frame, int end_frame, const Time& frame_time);
		Sprite(const Sprite& other);
		Sprite& operator=(const Sprite& other);
		~Sprite();
		void setFrameTime(const Time& frame_time);
		void setFrameInterval(int begin_frame, int end_frame);
		void setFrameSize(const Vector2d& frame_size);
		void setFrameMargin(const Vector2d& frame_margin);
		const Time& getFrameTime() const;
		const std::vector<int>& getFrameOrder() const;
		Vector2d getFrameSize() const;
		Vector2d getFrameMargin() const;
		const Texture& getTexture() const;
		Texture& getTexture();
		void setCenter(const Vector2d& center);
		const Vector2d& getCenter() const;

	private:
		Texture m_texture;
		Time m_time_left;
		Time m_frame_time;
		Vector2d m_frame_size;
		Vector2d m_frame_margin;
		Vector2d m_center;
		int m_current_frame;
		std::vector<int> m_frame_order;
	};
}
#endif
