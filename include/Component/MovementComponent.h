#pragma once

#include "MultiExtendAPI.h"

#include "Component/BasicComponent.h"

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
		Vector3 GetForwardSpeed() const;

		void SetAngularSpeed(float speed);
		void SetForwardSpeed(float speed);

	private:
		// rotation (radians/second)
		Vector3 m_AngularSpeed;
		
		// forward (units/second)
		Vector3 m_ForwardSpeed;
	};
}