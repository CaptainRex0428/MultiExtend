#pragma once

#include "MultiExtendAPI.h"

namespace MultiExtend
{
	class IUpdate
	{
	public:

		MULTIEXTEND_API virtual void Update(float delta) = 0;
		MULTIEXTEND_API virtual void CustomUpdate(float delta) = 0;
	};
}