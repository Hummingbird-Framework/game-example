#include "CollisionComponent.h"
using namespace hb;

bool CollisionComponent::s_collisions_executed = false;
std::set<CollisionComponent*> CollisionComponent::s_components = std::set<CollisionComponent*>();

CollisionComponent::CollisionComponent(const Vector2d& size):
m_size(size)
{
	m_me = s_components.insert(this).first;
}


CollisionComponent::~CollisionComponent()
{
	s_components.erase(m_me);
}


void CollisionComponent::executeCollisions()
{
	for (std::set<CollisionComponent*>::iterator i = s_components.begin(); i != s_components.end(); ++i)
		for (std::set<CollisionComponent*>::iterator j = i; j != s_components.end(); ++j)
		{
			if (i == j) continue;
			Rect intersection;
			Vector3d p_i = (*i)->getGameObject()->getPosition() + (*i)->getPosition();
			Vector3d p_j = (*j)->getGameObject()->getPosition() + (*j)->getPosition();
			Rect r_i = Rect(p_i.x, p_i.y, (*i)->m_size.x, (*i)->m_size.y);
			Rect r_j = Rect(p_j.x, p_j.y, (*j)->m_size.x, (*j)->m_size.y);
			if (r_i.intersects(r_j, intersection))
			{
				(*i)->m_collisions.push(Collision{intersection, (*j)->getGameObject()});
				(*j)->m_collisions.push(Collision{intersection, (*i)->getGameObject()});
			}
		}
}


void CollisionComponent::preUpdate()
{
	if (not s_collisions_executed)
	{
		executeCollisions();
		s_collisions_executed = true;
	}
}


void CollisionComponent::postUpdate()
{
	if (s_collisions_executed)
		s_collisions_executed = false;
	while(!m_collisions.empty())
		m_collisions.pop();
}


CollisionComponent::Collision CollisionComponent::nextCollision()
{
	Collision g = m_collisions.front();
	m_collisions.pop();
	return g;
}


bool CollisionComponent::empty() const
{
	return m_collisions.empty();
}


void CollisionComponent::setSize(const Vector2d& size)
{
	m_size = size;
}


const Vector2d& CollisionComponent::getSize() const
{
	return m_size;
}
