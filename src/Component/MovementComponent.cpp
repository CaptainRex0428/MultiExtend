#include "Component/MovementComponent.h"

#include "Actor/Actor.h"

MultiExtend::MovementComponent::MovementComponent(
	Actor* Owner,
	const char* tag,
	int updateorder)
	:BasicComponent(Owner, tag, updateorder), 
	m_AngularSpeed(0), m_ForwardSpeed(0)
{
}

MultiExtend::MovementComponent::~MovementComponent()
{
}

void MultiExtend::MovementComponent::Update(float deltaTime)
{
	if(!Math::NearZero(m_AngularSpeed))
	{
		Vector3 rot = GetOwner()->GetRotationRelative();

		rot += (m_AngularSpeed * deltaTime);

		GetOwner()->SetRotationRelative(rot);
	}

	if (!Math::NearZero(m_ForwardSpeed))
	{
		Vector3 pos = GetOwner()->GetPositionRelative();
		
		pos += m_ForwardSpeed * deltaTime;

		GetOwner()->SetPositionRelative(pos);
	}
}

MultiExtend::Vector3 MultiExtend::MovementComponent::GetAngularSpeed() const
{
	return m_AngularSpeed;
}

MultiExtend::Vector3 MultiExtend::MovementComponent::GetForwardSpeed() const
{
	return m_ForwardSpeed;
}

void MultiExtend::MovementComponent::SetAngularSpeed(float speed)
{
	m_AngularSpeed = speed;
}

void MultiExtend::MovementComponent::SetForwardSpeed(float speed)
{
	m_ForwardSpeed = speed;
}
