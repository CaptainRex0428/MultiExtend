#pragma once

#include "MultiExtendAPI.h"
#include <cmath>

namespace MultiExtend
{
	class IInput
	{
	public:

		MULTIEXTEND_API virtual void ProcessInput(const uint8_t * keyState) = 0;
		MULTIEXTEND_API virtual void CustomInput(const uint8_t * keyState) = 0;
	};
}