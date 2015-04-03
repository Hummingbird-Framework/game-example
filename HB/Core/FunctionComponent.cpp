#include "FunctionComponent.h"
using namespace hb;

FunctionComponent::FunctionComponent()
{

}


FunctionComponent::~FunctionComponent()
{
	for(auto x : m_vector_of_listener_id)
		getGameObject()->getMessageManager().ignore(x);
}


void FunctionComponent::addListener(const std::string& name, std::function<void(DataRepository&)>&& listener)
{
	hb_assert(getGameObject() != nullptr, "Added listener to FunctionComponent before it being added to a GameObject.");
	getGameObject()->getMessageManager().listen(name, std::move(listener));
}
