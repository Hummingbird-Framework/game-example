#include "Wall.h"

Wall::Wall(hb::RenderWindowManager* window_manager, const hb::Vector2d& size)
{
	m_collider = new hb::CollisionComponent(size);
	m_sprite = new hb::SpriteComponent(window_manager);
	hb::Vector2d sp_size = m_sprite->getSize();
	m_sprite->setScale(hb::Vector3d(size.x/sp_size.x, size.y/sp_size.y, 1));
	m_sprite->setPosition(hb::Vector3d(0,0,0));

	mousebuttonworld_listener_id = hb::InputManager::instance()->listen([this](const hb::MouseButtonWorld& e)
	{
		getGameObject()->setPosition(hb::Vector3d(e.x, e.y, getGameObject()->getPosition().z));
	});
}

Wall::~Wall()
{
	hb::InputManager::instance()->ignore(mousebuttonworld_listener_id);
}


void Wall::init()
{
	getGameObject()->addComponent(m_collider);
	getGameObject()->addComponent(m_sprite);
}