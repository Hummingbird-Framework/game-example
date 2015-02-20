#include "TextureManager.h"
#include <iostream>
using namespace hb;

TextureManager* TextureManager::s_instance = NULL;


TextureManager::TextureManager():
ResourceManager<sf::Texture, detail::tex_id>()
{
	sf::Image i404;
	sf::Color c1 (41, 128, 185);
	sf::Color c2 (39, 174, 96);
	i404.create(64, 64, c1);
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; j+=2)
			for (int k = 0; k < 16; ++k)
				for (int l = 0; l < 16; ++l)
				{
					int p = 0;
					if (i%2 == 1) p = 16;
					i404.setPixel(p + l + 16 * j, k + 16 * i, c2);
					assert(p + l + 16 * j < 64);
					assert(k + 16 * i < 64);
				}

	sf::Texture t404;
	t404.create(64, 64);
	t404.update(i404);
	this->t404 = this->addResource(makeTexId("t404", sf::IntRect()), t404);
}


TextureManager* TextureManager::instance()
{
	if (s_instance == NULL)
		s_instance = new TextureManager();

	return s_instance;
}


/* Load a Texture resource from file and return its id.
   Returns -1 if error while loading texture. */
int TextureManager::loadFromFile(const std::string& path, const sf::IntRect& area)
{
	sf::Texture tex;
	if (!isLoaded(path, area))
		if (!tex.loadFromFile(path, area))
			return t404;

	return this->addResource(makeTexId(path, area), tex);
}


void TextureManager::release(int id)
{
	if (id == t404) return;
	ResourceManager::release(id);
}


bool TextureManager::isLoaded(const std::string& path, const sf::IntRect& area) const
{
	return ResourceManager<sf::Texture, detail::tex_id>::isLoaded(makeTexId(path, area));
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