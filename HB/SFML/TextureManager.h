#ifndef HB_TEXTURE_MANAGER_H
#define HB_TEXTURE_MANAGER_H
#include <string>
#include <SFML/Graphics.hpp>
#include "hash_pair.h"
#include "../Base/ResourceManager.h"

namespace hb
{
	namespace detail
	{
		typedef std::pair<int, int> pair_int;
		typedef std::pair<pair_int, pair_int> pair2_int;
		typedef std::pair<std::string, pair2_int> tex_id;
	}

	class TextureManager : public ResourceManager<sf::Texture, detail::tex_id>
	{
	public:
		static TextureManager* instance();
		/* Load a Texture resource from file and return its id.
		   Returns -1 if error while loading texture. */
		int loadFromFile(const std::string& path, const sf::IntRect& area = sf::IntRect());
		bool isLoaded(const std::string& path, const sf::IntRect& area = sf::IntRect()) const;
		void release(int id) override;
		int getT404() const;

	private:
		TextureManager();
		static detail::tex_id makeTexId(const std::string& path, const sf::IntRect& area);
		static TextureManager* s_instance;
		int t404;
	};
}
#endif
