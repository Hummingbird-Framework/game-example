#include "SpriteComponent.h"
using namespace hb;

SpriteComponent::Animation::Animation(const std::string& path, const sf::IntRect& area, const Vector2d& frame_size, const Vector2d& frame_margin, int begin_frame, int end_frame, const Time& frame_time):
m_path(path),
m_area(area),
m_time_left(frame_time),
m_frame_time(frame_time),
m_frame_size(frame_size),
m_frame_margin(frame_margin),
m_begin_frame(begin_frame),
m_current_frame(begin_frame),
m_end_frame(end_frame),
m_texture_id(-1)
{
	setTexture(path, area);
}


SpriteComponent::Animation::Animation(const SpriteComponent::Animation& other):
m_path(other.m_path),
m_area(other.m_area),
m_time_left(other.m_time_left),
m_frame_time(other.m_frame_time),
m_frame_size(other.m_frame_size),
m_frame_margin(other.m_frame_margin),
m_begin_frame(other.m_begin_frame),
m_current_frame(other.m_current_frame),
m_end_frame(other.m_end_frame),
m_texture_id(-1)
{
	setTexture(m_path, m_area);
}


SpriteComponent::Animation& SpriteComponent::Animation::operator=(const SpriteComponent::Animation& other)
{
	m_path = other.m_path;
	m_area = other.m_area;
	m_time_left = other.m_time_left;
	m_frame_time = other.m_frame_time;
	m_frame_size = other.m_frame_size;
	m_frame_margin = other.m_frame_margin;
	m_begin_frame = other.m_begin_frame;
	m_current_frame = other.m_current_frame;
	m_end_frame = other.m_end_frame;
	m_texture_id = -1;	
	setTexture(m_path, m_area);
	return *this;
}


SpriteComponent::Animation::~Animation()
{
	TextureManager::instance()->release(m_texture_id);
}


void SpriteComponent::Animation::setTexture(const std::string& path, const sf::IntRect& area)
{
	if (m_texture_id != -1)
		TextureManager::instance()->release(m_texture_id);
	m_texture_id = TextureManager::instance()->loadFromFile(path, area);
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
