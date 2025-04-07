#pragma once

#include "MultiExtendAPI.h"
#include "Math/Vector.h"

namespace MultiExtend
{
	class ITransform
	{
	public:
		MULTIEXTEND_API virtual const Vector3& GetPositionRelative() const = 0;
		MULTIEXTEND_API virtual const Vector3& GetScaleRelative() const = 0;
		MULTIEXTEND_API virtual const Vector3& GetRotationRelative() const = 0;

		MULTIEXTEND_API virtual void SetPositionRelative(Vector3 pos) = 0;
		MULTIEXTEND_API virtual void SetScaleRelative(Vector3 scale) = 0;
		MULTIEXTEND_API virtual void SetRotationRelative(Vector3 rotation) = 0;

		MULTIEXTEND_API virtual const Vector3 GetPositionAbsolute() const = 0;
		MULTIEXTEND_API virtual const Vector3 GetScaleAbsolute() const = 0;
		MULTIEXTEND_API virtual const Vector3 GetRotationAbsolute() const = 0;
	};
}