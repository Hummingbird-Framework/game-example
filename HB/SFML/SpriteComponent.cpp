#include "SpriteComponent.h"
using namespace hb;


SpriteComponent::SpriteComponent(const Sprite& sprite):
GameObject::Component(),
m_time_left(Time::seconds(0)),
m_current_frame(0),
m_visible(true),
m_playing(true),
m_looping(true),
m_sprite()
{
	setSprite(sprite);
}


SpriteComponent::~SpriteComponent()
{

}


void SpriteComponent::setSprite(const Sprite& sprite)
{
	m_animation = sprite;
	m_current_frame = sprite.m_current_frame;
	m_sprite.setTexture(m_animation.m_texture.get());
	m_sprite.setOrigin(sprite.m_center.x, sprite.m_center.y);
	if (m_animation.m_frame_time.asMiliseconds() == 0)
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
				m_time_left = m_animation.m_frame_time + m_time_left;
				m_current_frame++;
				if (m_current_frame >= m_animation.m_frame_order.size())
				{
					if (m_looping)
						m_current_frame = 0;
					else
					{
						stop();
						m_current_frame--;
					}
				}

			}
		}
		Vector2d pos = getCoords();
		m_sprite.setTextureRect(sf::IntRect(pos.x, pos.y, m_animation.m_frame_size.x, m_animation.m_frame_size.y));
		Vector3d p = getPosition() + getGameObject()->getPosition();
		Camera camera = Renderer::getCamera();
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
	int x_coord = (m_animation.m_frame_order[m_current_frame] % nx) * (m_animation.m_frame_size.x + m_animation.m_frame_margin.x) + m_animation.m_frame_margin.x;
	int y_coord = (m_animation.m_frame_order[m_current_frame] / nx) * (m_animation.m_frame_size.y + m_animation.m_frame_margin.y) + m_animation.m_frame_margin.y;
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