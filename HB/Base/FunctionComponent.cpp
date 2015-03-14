#include "FunctionComponent.h"
using namespace hb;

FunctionComponent::FunctionComponent()
{
	m_pre_update = [&] () {};
	m_update = [&] () {};
	m_post_update = [&] () {};
	m_destroy = [&] () {};
}


FunctionComponent::~FunctionComponent()
{
	m_destroy();
}


void FunctionComponent::setPreUpdateFunction(std::function<void(void)> pre_update)
{
	m_pre_update = pre_update;
}


void FunctionComponent::setUpdateFunction(std::function<void(void)> update)
{
	m_update = update;
}


void FunctionComponent::setPostUpdateFunction(std::function<void(void)> post_update)
{
	m_post_update = post_update;
}


void FunctionComponent::setDestroyFunction(std::function<void(void)> destroy)
{
	m_destroy = destroy;
}


void FunctionComponent::preUpdate()
{
	m_pre_update();
}


void FunctionComponent::update()
{
	m_update();
}


void FunctionComponent::postUpdate()
{
	m_post_update();
}
