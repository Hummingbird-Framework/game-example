#ifndef HB_TEXTURE_H
#define HB_TEXTURE_H
#include <sstream>
#include "../Core/Resource.h"
#include "../Core/Vector2d.h"
#include "../Core/Color.h"
#include "TextureManager.h"
#include "Rect.h"

namespace hb
{
	/**
	 * \class Texture
	 * \ingroup SFML
	 */
	class Texture : public Resource<sf::Texture, detail::tex_id, TextureManager>
	{
	public:
		Texture(const sf::Texture& texture, const detail::tex_id& id);
		Texture(const detail::tex_id& id);
		~Texture();
		static Texture t404();
		static Texture loadFromFile(const std::string& path, const Rect& area = Rect());
		static Texture makeTexture(const Vector2d& size);
		void fill(const Rect& area, const Color& color);
		void stroke(const Vector2d& start, const Vector2d& end, const Color& color);
		Vector2d size() const;
		void smooth(bool smooth);
		void repeat(bool repeat);
	};
}
#endif