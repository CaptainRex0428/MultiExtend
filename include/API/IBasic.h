#pragma once

#include "MultiExtendAPI.h"

#include <cmath>

namespace MultiExtend
{
	enum State : int
	{
		State_VALID =		0b00000001,
		State_INPUT =		0b00000010,
		State_UPDATE =		0b00000100,
		State_DISPLAY =		0b00001000,
	};

	enum StateTag : uint8_t
	{
		Tag_VALID,
		Tag_INPUT,
		Tag_UPDATE,
		Tag_DISPLAY
	};


	class IBasic
	{
	public:

		MULTIEXTEND_API virtual const char* GetTag() const = 0;
		MULTIEXTEND_API virtual void SetTag(const char* type) = 0;
		MULTIEXTEND_API virtual const int& GetUpdateOrder() const = 0;
		MULTIEXTEND_API virtual void SetUpdateOrder(int order) = 0;

		MULTIEXTEND_API virtual int  GetState() const = 0;
		MULTIEXTEND_API virtual bool GetState(StateTag tag) const = 0;
		MULTIEXTEND_API virtual void SetState(int state) = 0;
		MULTIEXTEND_API virtual void ToggleState(StateTag tag) = 0;
	};
}