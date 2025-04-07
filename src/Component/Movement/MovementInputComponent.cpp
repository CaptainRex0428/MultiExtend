#include "Component/Movement/MovementInputComponent.h"

MultiExtend::MovementInputComponent::MovementInputComponent(
	IComponentOwner* Owner, const char* tag, int updateorder)
	:MovementComponent(Owner,tag,updateorder)
{
	
}

MultiExtend::MovementInputComponent::~MovementInputComponent()
{
}

void MultiExtend::MovementInputComponent::ProcessInput(const uint8_t* keyState)
{
	float forwardSpeed = 0;

	if(keyState[m_ForwardKey])
	{
		forwardSpeed += MaxForwardSpeed;
	}

	if(keyState[m_BackwardKey])
	{
		forwardSpeed -= MaxForwardSpeed;
	}

	SetForwardSpeed(forwardSpeed);

	Vector3 AngularSpeed = 0;

	if(keyState[m_ClockWiseKey])
	{
		AngularSpeed += MaxAngularSpeed;
	}

	if(keyState[m_CounterClockWiseKey])
	{
		AngularSpeed -= MaxAngularSpeed;
	}

	SetAngularSpeed(AngularSpeed);

	MovementComponent::ProcessInput(keyState);
}

void MultiExtend::MovementInputComponent::CustomInput(const uint8_t* keyState)
{
	
}