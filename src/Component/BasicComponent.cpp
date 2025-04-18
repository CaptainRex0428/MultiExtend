#include "Component/BasicComponent.h"
#include "Actor/Actor.h"

MultiExtend::BasicComponent::BasicComponent(
	IComponentOwner* Owner,
	const char* tag,
	int updateorder)
	:Component(tag, updateorder), m_Owner(Owner)
{

}

MultiExtend::BasicComponent::~BasicComponent()
{

}

MultiExtend::IComponentOwner* MultiExtend::BasicComponent::GetOwner() const
{
	return m_Owner;
}

void MultiExtend::BasicComponent::SetOwner(IComponentOwner* owner)
{
	this->m_Owner = owner;
}

