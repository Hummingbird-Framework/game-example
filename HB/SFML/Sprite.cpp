#include "Sprite.h"
using namespace hb;

Sprite::Sprite(const Texture& texture, const Vector2d& frame_size, const Vector2d& frame_margin):
m_texture(texture),
m_frame_size(frame_size),
m_frame_margin(frame_margin)
{
	if (m_frame_size.x == -1)
		m_frame_size.x = texture.size().x;
	if (m_frame_size.y == -1)
		m_frame_size.y = texture.size().y;
	
}


Sprite::Sprite(const Sprite& other):
m_texture(other.m_texture),
m_frame_size(other.m_frame_size),
m_frame_margin(other.m_frame_margin)
{

}


Sprite& Sprite::operator=(const Sprite& other)
{
	m_texture = other.m_texture;
	m_frame_size = other.m_frame_size;
	m_frame_margin = other.m_frame_margin;
	return *this;
}


Sprite::~Sprite()
{

}


void Sprite::setFrameSize(const Vector2d& frame_size)
{
	m_frame_size = frame_size;
}


void Sprite::setFrameMargin(const Vector2d& frame_margin)
{
	m_frame_margin = frame_margin;
}


Vector2d Sprite::getFrameSize() const
{
	return m_frame_size;
}


Vector2d Sprite::getFrameMargin() const
{
	return m_frame_margin;
}

const Texture& Sprite::getTexture() const
{
	return m_texture;
}


Texture& Sprite::getTexture()
{
	return m_texture;
}


void Sprite::setCenter(const Vector2d& center)
{
	m_center = center;
}


const Vector2d& Sprite::getCenter() const
{
	return m_center;
}
