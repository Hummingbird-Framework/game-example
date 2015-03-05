#include "SpriteComponent.h"
using namespace hb;


SpriteComponent::SpriteComponent(RenderWindowManager* render_manager, const Sprite& sprite):
GameObject::Component(),
m_time_left(Time::seconds(0)),
m_current_frame(0),
m_visible(true),
m_playing(true),
m_looping(true),
m_sprite(sf::Sprite()),
m_render_manager(render_manager)
{
	setSprite(sprite);
}


SpriteComponent::~SpriteComponent()
{

}


void SpriteComponent::setRenderWindowManager(RenderWindowManager* render_manager)
{
	m_render_manager = render_manager;
}

void SpriteComponent::setSprite(const Sprite& sprite)
{
	m_animation = sprite;
	m_current_frame = sprite.m_current_frame;
	m_sprite.setTexture(m_animation.m_texture.get());
	if (m_animation.m_frame_time.asMiliseconds() == 0)
		stop();
}

RenderWindowManager* SpriteComponent::getRenderWindowManager()
{
	return m_render_manager;
}


const RenderWindowManager* SpriteComponent::getRenderWindowManager() const
{
	return m_render_manager;
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
				if (m_current_frame > m_animation.m_end_frame)
				{
					if (m_looping)
						m_current_frame = m_animation.m_begin_frame;
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

		float x = getPosition().x + getGameObject()->getPosition().x;
		float y = getPosition().y + getGameObject()->getPosition().y;
		m_sprite.setPosition(x, y);
		x = getScale().x * getGameObject()->getScale().x;
		y = getScale().y * getGameObject()->getScale().y;
		m_sprite.setScale(x, y);
		x = getRotation().z + getGameObject()->getRotation().z;
		m_sprite.setRotation(x);
		double z_index = getPosition().z + getGameObject()->getPosition().z;
		m_render_manager->addDrawable(std::pair<double, sf::Sprite>(z_index, m_sprite));
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
	int x_coord = (m_current_frame % nx) * (m_animation.m_frame_size.x + m_animation.m_frame_margin.x) + m_animation.m_frame_margin.x;
	int y_coord = (m_current_frame / nx) * (m_animation.m_frame_size.y + m_animation.m_frame_margin.y) + m_animation.m_frame_margin.y;
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