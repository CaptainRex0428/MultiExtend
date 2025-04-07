#pragma once

#include "MultiExtendAPI.h"
#include "MovementComponentConfig.h"

#include "Component/BasicComponent.h"
#include "Math/Math.h"
#include "Math/Vector.h"

namespace MultiExtend
{
	class MovementComponent : public BasicComponent
	{
	public:
		MULTIEXTEND_API MovementComponent(
			IComponentOwner* Owner = nullptr,
			const char* tag = DEFAULT_MOVEMENTCOMPONENTNAME,
			int updateorder = DEFAULT_MOVEMENTCOMPONENTUPDATEORDER);

		MULTIEXTEND_API virtual ~MovementComponent();

		MULTIEXTEND_API virtual void CustomInput(const uint8_t* keyState) override {};
		MULTIEXTEND_API virtual void CustomUpdate(float delta) override;
		MULTIEXTEND_API virtual void CustomDraw() override {};

		Vector3 GetAngularSpeed() const;
		float GetForwardSpeed() const;
		Vector3 GetForwardDirectRelative() const;

		void SetAngularSpeed(Vector3 speed);
		void SetForwardSpeed(float speed);

	private:
		// rotation (degree/second)
		Vector3 m_AngularSpeed;
		
		// forward (units/second)
		float m_ForwardSpeed;
	};
}