#pragma once

#include "MultiExtendAPI.h"
#include "Component/BasicComponent.h"
#include "Math/Math.h"

namespace MultiExtend
{
	class MovementComponent : public BasicComponent
	{
	public:
		MULTIEXTEND_API MovementComponent(
			Actor* Owner = nullptr,
			const char* tag = DEFAULT_BASICCOMPONENTNAME,
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API virtual ~MovementComponent();

		MULTIEXTEND_API void Update(float deltaTime) override; 

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