#pragma once

#include "MultiExtendAPI.h"
#include <cmath>

namespace MultiExtend
{
	class IDraw
	{
	public:
		MULTIEXTEND_API virtual void Draw() = 0;
		MULTIEXTEND_API virtual void CustomDraw() = 0;
	};
}