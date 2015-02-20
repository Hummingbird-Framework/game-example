#include "FunctionComponent.h"
using namespace hb;

FunctionComponent::FunctionComponent()
{
	m_pre_update = [&] (GameObject*) {};
	m_update = [&] (GameObject*) {};
	m_post_update = [&] (GameObject*) {};
}


void FunctionComponent::setPreUpdateFunction(std::function<void(GameObject*)> pre_update)
{
	m_pre_update = pre_update;
}


void FunctionComponent::setUpdateFunction(std::function<void(GameObject*)> update)
{
	m_update = update;
}


void FunctionComponent::setPostUpdateFunction(std::function<void(GameObject*)> post_update)
{
	m_post_update = post_update;
}


void FunctionComponent::preUpdate()
{
	m_pre_update(getGameObject());
}


void FunctionComponent::update()
{
	m_update(getGameObject());
}


void FunctionComponent::postUpdate()
{
	m_post_update(getGameObject());
}
