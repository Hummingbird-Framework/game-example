#include "Texture.h"
using namespace hb;

Texture::Texture(const sf::Texture& texture, const detail::tex_id& id):
Resource<sf::Texture, detail::tex_id, TextureManager>(texture, id)
{

}


Texture::Texture(const detail::tex_id& id):
Resource<sf::Texture, detail::tex_id, TextureManager>(id)
{

}


Texture::~Texture()
{

}


Texture Texture::t404()
{
	TextureManager* TM = TextureManager::instance();
	return Texture(TM->getId(TM->getT404()));
}


Texture Texture::loadFromFile(const std::string& path, const Rect& area)
{
	TextureManager* TM = TextureManager::instance();
	sf::IntRect area_sf = sf::IntRect(area);
	if (TM->isLoaded(path, area_sf))
		return Texture(TextureManager::makeTexId(path, area_sf));
	else
	{
		sf::Texture tex;
		if (!tex.loadFromFile(path, area_sf))
		{
			return t404();
		}
		return Texture(tex, TextureManager::makeTexId(path, area_sf));
	}

}


Texture Texture::makeTexture(const Vector2d& size)
{
	sf::Texture tex;
	tex.create(size.x, size.y);
	std::stringstream ss;
	ss << "tex_" << TextureManager::instance()->resourceCount();
	Texture texture = Texture(tex, TextureManager::makeTexId(ss.str(), sf::IntRect(0, 0, size.x, size.y)));
	return texture;
}


void Texture::fill(const Rect& area, const Color& color)
{
	sf::Image img = get().copyToImage();
	sf::Color c (color.r*255, color.g*255, color.b*255, color.a*255);
	for (int i = 0; i < area.width; ++i)
		for (int j = 0; j < area.height; ++j)
			img.setPixel(area.left + i, area.top + j, c);

	get().update(img);
}


void Texture::stroke(const Vector2d& start, const Vector2d& end, const Color& color)
{
	sf::Image img = get().copyToImage();
	sf::Color c (color.r*255, color.g*255, color.b*255, color.a*255);

	Vector2d delta = end - start;
	int steps = delta.module() + 0.5;

	delta = delta.normalized();

	for (int i = 0; i <= steps; ++i)
	{
		img.setPixel(start.x + (i * delta).x, start.y + (i * delta).y, c);
	}

	get().update(img);
}


Vector2d Texture::size() const
{
	sf::Vector2u s = TextureManager::instance()->get(m_id).getSize();
	return Vector2d(s.x, s.y);
}


void Texture::smooth(bool smooth)
{
	TextureManager::instance()->get(m_id).setSmooth(smooth);
}


void Texture::repeat(bool repeat)
{
	TextureManager::instance()->get(m_id).setRepeated(repeat);
}
