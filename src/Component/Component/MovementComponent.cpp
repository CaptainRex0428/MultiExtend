#include "Component/Movement/MovementComponent.h"

#include "Actor/Actor.h"
#include "Math/Matrix.h"

MultiExtend::MovementComponent::MovementComponent(
	Actor* Owner,
	const char* tag,
	int updateorder)
	:BasicComponent(Owner, tag, updateorder), 
	m_AngularSpeed(Vector3{0,0,0}), m_ForwardSpeed(0)
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
		
		pos += GetForwardDirectRelative() * m_ForwardSpeed * deltaTime;

		GetOwner()->SetPositionRelative(pos);
	}
}

MultiExtend::Vector3 MultiExtend::MovementComponent::GetAngularSpeed() const
{
	return m_AngularSpeed;
}

float MultiExtend::MovementComponent::GetForwardSpeed() const
{
	return m_ForwardSpeed;
}

MultiExtend::Vector3 MultiExtend::MovementComponent::GetForwardDirectRelative() const
{
	Vector3 rot = GetOwner()->GetRotationRelative();
	Vector3 basicDirect {1,0,0};

	Matrix4x4 rotationMatrix = MTXRotationZ(rot[z]) * MTXRotationY(rot[y]) * MTXRotationX(rot[x]);
	
	Matrix4x1 rotationRelativeResult = rotationMatrix * basicDirect;

	return Vector3{ rotationRelativeResult[0],rotationRelativeResult[1],rotationRelativeResult[2] };
}

void MultiExtend::MovementComponent::SetAngularSpeed(Vector3 speed)
{
	m_AngularSpeed = speed;
}

void MultiExtend::MovementComponent::SetForwardSpeed(float speed)
{
	m_ForwardSpeed = speed;
}