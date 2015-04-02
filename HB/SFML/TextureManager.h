#ifndef HB_TEXTURE_MANAGER_H
#define HB_TEXTURE_MANAGER_H
#include <string>
#include <SFML/Graphics.hpp>
#include "hash_pair.h"
#include "../Core/ResourceManager.h"

namespace hb
{
	namespace detail
	{
		typedef std::pair<int, int> pair_int;
		typedef std::pair<pair_int, pair_int> pair2_int;
		typedef std::pair<std::string, pair2_int> tex_id;
	}

	/**
	 * \class TextureManager
	 * \ingroup SFML
	 */
	class TextureManager : public ResourceManager<TextureManager, sf::Texture, detail::tex_id>
	{
	public:
		TextureManager();
		static detail::tex_id makeTexId(const std::string& path, const sf::IntRect& area);
		using ResourceManager<TextureManager, sf::Texture, detail::tex_id>::isLoaded;
		bool isLoaded(const std::string& path, const sf::IntRect& area = sf::IntRect()) const;
		void release(int id) override;
		int getT404() const;

	private:
		int t404;
	};
}
#endif
