#include "Sprite.h"
using namespace hb;

Sprite::Sprite(const Texture& texture, const Vector2d& frame_size, const Vector2d& frame_margin, int begin_frame, int end_frame, const Time& frame_time):
m_texture(texture),
m_time_left(frame_time),
m_frame_time(frame_time),
m_frame_size(frame_size),
m_frame_margin(frame_margin),
m_begin_frame(begin_frame),
m_current_frame(begin_frame),
m_end_frame(end_frame)
{

}


Sprite::Sprite(const Sprite& other):
m_texture(other.m_texture),
m_time_left(other.m_time_left),
m_frame_time(other.m_frame_time),
m_frame_size(other.m_frame_size),
m_frame_margin(other.m_frame_margin),
m_begin_frame(other.m_begin_frame),
m_current_frame(other.m_current_frame),
m_end_frame(other.m_end_frame)
{

}


Sprite& Sprite::operator=(const Sprite& other)
{
	m_texture = other.m_texture;
	m_time_left = other.m_time_left;
	m_frame_time = other.m_frame_time;
	m_frame_size = other.m_frame_size;
	m_frame_margin = other.m_frame_margin;
	m_begin_frame = other.m_begin_frame;
	m_current_frame = other.m_current_frame;
	m_end_frame = other.m_end_frame;
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
	m_begin_frame = begin_frame;
	m_end_frame = end_frame;
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


std::pair<int, int> Sprite::getFrameInterval() const
{
	return std::pair<int, int>(m_begin_frame, m_end_frame);
}


Vector2d Sprite::getFrameSize() const
{
	return m_frame_size;
}


Vector2d Sprite::getFrameMargin() const
{
	return m_frame_margin;
}
