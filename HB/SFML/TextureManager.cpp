#include "TextureManager.h"
using namespace hb;


TextureManager::TextureManager():
ResourceManager<TextureManager, sf::Texture, detail::tex_id>()
{
	sf::Image i404;
	sf::Color c1 (40, 117, 154); // Blue
	sf::Color c2 (39, 174, 96);  // Green
	i404.create(64, 64, c1);
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; j+=2)
			for (int k = 0; k < 16; ++k)
				for (int l = 0; l < 16; ++l)
				{
					int p = 0;
					if (i%2 == 1) p = 16;
					i404.setPixel(p + l + 16 * j, k + 16 * i, c2);
				}

	sf::Texture t404;
	t404.create(64, 64);
	t404.update(i404);
	this->t404 = this->addResource(makeTexId("t404", sf::IntRect()), t404);
	get(this->t404).setRepeated(true);
}


void TextureManager::release(int id)
{
	if (id == t404) return;
	ResourceManager::release(id);
}


bool TextureManager::isLoaded(const std::string& path, const sf::IntRect& area) const
{
	return ResourceManager<TextureManager, sf::Texture, detail::tex_id>::isLoaded(makeTexId(path, area));
}


detail::tex_id TextureManager::makeTexId(const std::string& path, const sf::IntRect& area)
{
	detail::pair_int p1(area.left, area.top);
	detail::pair_int p2(area.width, area.height);
	detail::pair2_int p3(p1, p2);
	detail::tex_id id(path, p3);
	return id;
}

int TextureManager::getT404() const
{
	return t404;
}