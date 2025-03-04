#pragma once

#include "MultiExtendAPI.h"
#include "System/Hash/HashGenerator.h"
#include "Time/Clock/Clock.h"
#include "System/Operator.h"

namespace MultiExtend
{
	class Object
	{
	public:
		MULTIEXTEND_API Object();
		MULTIEXTEND_API virtual ~Object();

		MULTIEXTEND_API const tm* GetConstructedTime();

		template <typename T>
		MULTIEXTEND_API bool IsA()
		{
			return static_cast<T*>(this);
		};

	private:
		const tm * m_constructedTime;
	};
}