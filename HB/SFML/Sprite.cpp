#include "Sprite.h"
using namespace hb;

Sprite::Sprite(const Texture& texture, const Vector2d& frame_size, const Vector2d& frame_margin, int begin_frame, int end_frame, const Time& frame_time):
m_texture(texture),
m_time_left(frame_time),
m_frame_time(frame_time),
m_frame_size(frame_size),
m_frame_margin(frame_margin),
m_current_frame(0)
{
	setFrameInterval(begin_frame, end_frame);
}


Sprite::Sprite(const Texture& texture, const Vector2d& frame_size, const Vector2d& frame_margin, const std::vector<int>& frame_order, const Time& frame_time):
m_texture(texture),
m_time_left(frame_time),
m_frame_time(frame_time),
m_frame_size(frame_size),
m_frame_margin(frame_margin),
m_current_frame(0),
m_frame_order(frame_order)
{

}


Sprite::Sprite(const Sprite& other):
m_texture(other.m_texture),
m_time_left(other.m_time_left),
m_frame_time(other.m_frame_time),
m_frame_size(other.m_frame_size),
m_frame_margin(other.m_frame_margin),
m_current_frame(other.m_current_frame),
m_frame_order(other.m_frame_order)
{

}


Sprite& Sprite::operator=(const Sprite& other)
{
	m_texture = other.m_texture;
	m_time_left = other.m_time_left;
	m_frame_time = other.m_frame_time;
	m_frame_size = other.m_frame_size;
	m_frame_margin = other.m_frame_margin;
	m_frame_order = other.m_frame_order;
	m_current_frame = other.m_current_frame;
	return *this;
}


Sprite::~Sprite()
{

}


void Sprite::setFrameTime(const Time& frame_time)
{
	m_frame_time = frame_time;
}


void Sprite::setFrameInterval(int begin_frame, int end_frame)
{
	int size = end_frame - begin_frame;
	m_frame_order.resize(size);
	for (int i = 0; i < size; ++i)
		m_frame_order[i] = begin_frame + i;
}


void Sprite::setFrameSize(const Vector2d& frame_size)
{
	m_frame_size = frame_size;
}


void Sprite::setFrameMargin(const Vector2d& frame_margin)
{
	m_frame_margin = frame_margin;
}

const Time& Sprite::getFrameTime() const
{
	return m_frame_time;
}


const std::vector<int>& Sprite::getFrameOrder() const
{
	return m_frame_order;
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
