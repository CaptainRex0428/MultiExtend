#pragma once

#include "MultiExtendAPI.h"
#include <cmath>

#include "Math/Vector.h"

namespace MultiExtend
{
	class IDraw
	{
	public:
		MULTIEXTEND_API virtual void Draw(const Vector2& size) = 0;
		MULTIEXTEND_API virtual void CustomDraw(const Vector2& size) = 0;
	};
}