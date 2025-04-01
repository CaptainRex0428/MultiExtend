#include "Component/BasicComponent.h"
#include "Actor/Actor.h"

MultiExtend::BasicComponent::BasicComponent(
	Actor* Owner,
	const char* tag,
	int updateorder)
	:Component(tag,updateorder),m_Owner(Owner)
{

}

MultiExtend::BasicComponent::~BasicComponent()
{
	
}

MultiExtend::Actor* MultiExtend::BasicComponent::GetOwner() const
{
	return m_Owner;
}

void MultiExtend::BasicComponent::SetOwner(Actor* owner)
{
	this->m_Owner = owner;
}
