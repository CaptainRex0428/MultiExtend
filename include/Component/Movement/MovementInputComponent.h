#pragma once

#include "MultiExtendAPI.h"
#include "MovementInputComponentConfig.h"

#include "MovementComponent.h"

namespace MultiExtend
{
	class MovementInputComponent : public MovementComponent
	{
		
		public:
			MULTIEXTEND_API MovementInputComponent(
				IComponentOwner* Owner = nullptr,
				const char* tag = DEFAULT_MOVEMENTINPUTCOMPONENTNAME,
				int updateorder = DEFAULT_MOVEMENTINPUTCOMPONENTUPDATEORDER);

			MULTIEXTEND_API virtual ~MovementInputComponent();

			MULTIEXTEND_API virtual void ProcessInput(const uint8_t* keyState) override;
			MULTIEXTEND_API virtual void CustomInput(const uint8_t* keyState) override;

	private:
		int m_ForwardKey;
		int m_BackwardKey;

		int m_ClockWiseKey;
		int m_CounterClockWiseKey;

		float MaxForwardSpeed;

		Vector3 MaxAngularSpeed;
	};
}