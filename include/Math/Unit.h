#pragma once

#include "MultiExtendAPI.h"

#include <tuple>

namespace MultiExtend
{
	enum MULTIEXTEND_API SystemSizeUnit
	{
		Byte = 0,
		KB = 1,
		MB = 2,
		GB = 3,
		TB = 4,
		PB = 5,
		EB = 6,
		ZB = 7,
		YB = 8
	};

	// transfer Byte size to specific unit output in double
	MULTIEXTEND_API double ByteSizeTo(int bytesize, SystemSizeUnit unit);

	// transfer Byte size to a proper unit output in double
	MULTIEXTEND_API std::tuple<const char*, double> ByteSizeConvert(uintmax_t bytesize);

}