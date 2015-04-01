#include "SpriteComponent.h"
using namespace hb;


SpriteComponent::SpriteComponent(const Sprite& sprite, const std::vector<int>& frame_order, const Time& frame_time):
GameObject::Component(),
m_time_left(Time::seconds(0)),
m_frame_time(frame_time),
m_current_frame(0),
m_visible(true),
m_playing(true),
m_looping(true),
m_sprite(),
m_frame_order(frame_order),
m_color(1.f, 1.f, 1.f, 1.f)
{
	hb_assert(frame_order.size() > 0, "You must define at least one frame for the frame order");
	setSprite(sprite);
}


SpriteComponent::~SpriteComponent()
{

}


void SpriteComponent::setSprite(const Sprite& sprite)
{
	m_animation = sprite;
	m_current_frame = 0;
	m_sprite.setTexture(m_animation.m_texture.get());
	m_sprite.setOrigin(sprite.m_center.x, sprite.m_center.y);
	if (m_frame_time.asMilliseconds() == 0)
		stop();
}


bool SpriteComponent::isVisible() const
{
	return m_visible;
}


void SpriteComponent::setVisible(bool visible)
{
	m_visible = visible;
}


void SpriteComponent::postUpdate()
{
	if (m_visible)
	{
		if (m_playing)
		{
			m_time_left -= Time::deltaTime;

			if (m_time_left <= Time())
			{
				m_time_left = m_frame_time + m_time_left;
				m_current_frame++;
				if (m_current_frame >= m_frame_order.size())
				{
					if (m_looping)
						m_current_frame = 0;
					else
					{
						stop();
						m_current_frame = m_frame_order.size()-1;
					}
				}

			}
		}
		Vector2d pos = getCoords();
		m_sprite.setTextureRect(sf::IntRect(pos.x, pos.y, m_animation.m_frame_size.x, m_animation.m_frame_size.y));
		Vector3d p = getPosition() + getGameObject()->getPosition();
		Camera& camera = Renderer::getCamera();
		Vector3d v = (camera.getAxisX() * p.x) + (camera.getAxisY() * p.y) + (camera.getAxisZ() * p.z);
		m_sprite.setPosition(v.x, v.y);
		double scale_x = getScale().x * getGameObject()->getScale().x;
		double scale_y = getScale().y * getGameObject()->getScale().y;
		m_sprite.setScale(scale_x, scale_y);
		double rotation = getRotation().z + getGameObject()->getRotation().z;
		m_sprite.setRotation(rotation);
		Renderer::addDrawable(std::pair<Vector3d, sf::Drawable*>(v, &m_sprite));
	}
}


bool SpriteComponent::isLooping() const
{
	return m_looping;
}


void SpriteComponent::loop(bool loop)
{
	m_looping = loop;
}


bool SpriteComponent::isPlaying() const
{
	return m_playing;
}


void SpriteComponent::play()
{
	m_playing = true;
}


void SpriteComponent::stop()
{
	m_playing = false;
}


Vector2d SpriteComponent::getCoords()
{
	if (m_animation.m_frame_size.x > m_sprite.getTexture()->getSize().x or m_animation.m_frame_size.y > m_sprite.getTexture()->getSize().y)
		return Vector2d();
	int nx = m_sprite.getTexture()->getSize().x / (m_animation.m_frame_size.x + m_animation.m_frame_margin.x);
	int x_coord = (m_frame_order[m_current_frame] % nx) * (m_animation.m_frame_size.x + m_animation.m_frame_margin.x) + m_animation.m_frame_margin.x;
	int y_coord = (m_frame_order[m_current_frame] / nx) * (m_animation.m_frame_size.y + m_animation.m_frame_margin.y) + m_animation.m_frame_margin.y;
	return Vector2d(x_coord, y_coord);
}


Vector2d SpriteComponent::getSize() const
{
	return m_animation.m_frame_size;
}

const Sprite& SpriteComponent::getSprite() const
{
	return m_animation;
}

Sprite& SpriteComponent::getSprite()
{
	return m_animation;
}


void SpriteComponent::setFrameOrder(const std::vector<int>& frame_order)
{
	hb_assert(frame_order.size() > 0, "You must define at least one frame for the frame order");
	m_frame_order = frame_order;
}


const std::vector<int>& SpriteComponent::getFrameOrder() const
{
	return m_frame_order;
}


void SpriteComponent::setFrameTime(const Time& frame_time)
{
	m_frame_time = frame_time;
}


const Time& SpriteComponent::getFrameTime() const
{
	return m_frame_time;
}


void SpriteComponent::setColor(const Color& color)
{
	m_color = color;
	m_sprite.setColor(sf::Color(color.r*255, color.g*255, color.b*255, color.a*255));
}


const Color& SpriteComponent::getColor() const
{
	return m_color;
}