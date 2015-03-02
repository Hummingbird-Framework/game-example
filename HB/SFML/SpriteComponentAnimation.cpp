#include "SpriteComponent.h"
using namespace hb;

SpriteComponent::Animation::Animation(const Texture& texture, const Vector2d& frame_size, const Vector2d& frame_margin, int begin_frame, int end_frame, const Time& frame_time):
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


SpriteComponent::Animation::Animation(const SpriteComponent::Animation& other):
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


SpriteComponent::Animation& SpriteComponent::Animation::operator=(const SpriteComponent::Animation& other)
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


SpriteComponent::Animation::~Animation()
{

}


void SpriteComponent::Animation::setFrameTime(const Time& frame_time)
{
	m_frame_time = frame_time;
}


void SpriteComponent::Animation::setFrameInterval(int begin_frame, int end_frame)
{
	m_begin_frame = begin_frame;
	m_end_frame = end_frame;
}


void SpriteComponent::Animation::setFrameSize(const Vector2d& frame_size)
{
	m_frame_size = frame_size;
}


void SpriteComponent::Animation::setFrameMargin(const Vector2d& frame_margin)
{
	m_frame_margin = frame_margin;
}
