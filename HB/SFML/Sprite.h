#ifndef HB_SPRITE_H
#define HB_SPRITE_H
#include <utility>
#include <vector>
#include "../Core/Time.h"
#include "../Core/Vector2d.h"
#include "Texture.h"

namespace hb
{
	/**
	 * \class Sprite
	 * \ingroup SFML
	 */
	class Sprite
	{
	public:
		friend class SpriteComponent;
		Sprite(const Texture& texture = Texture::t404(), const Vector2d& frame_size = Vector2d(-1, -1), const Vector2d& frame_margin = Vector2d(0, 0));
		Sprite(const Sprite& other);
		Sprite& operator=(const Sprite& other);
		~Sprite();
		void setFrameSize(const Vector2d& frame_size);
		void setFrameMargin(const Vector2d& frame_margin);
		Vector2d getFrameSize() const;
		Vector2d getFrameMargin() const;
		const Texture& getTexture() const;
		Texture& getTexture();
		void setCenter(const Vector2d& center);
		const Vector2d& getCenter() const;

	private:
		Texture m_texture;
		Vector2d m_frame_size;
		Vector2d m_frame_margin;
		Vector2d m_center;
	};
}
#endif
