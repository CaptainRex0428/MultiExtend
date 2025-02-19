#pragma once

#include <stdint.h>
#include <tuple>

#include "MultiExtendAPI.h"

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

	
	struct Math
	{
		MULTIEXTEND_API static int Clamp(int src, int min = 0, int max = 1);
		MULTIEXTEND_API static float Clamp(float src, float min = 0, float max = 1);
		MULTIEXTEND_API static uint8_t Clamp(uint8_t src, uint8_t min = 0, uint8_t max = 1);

		MULTIEXTEND_API static double& limit_min(double& src, double min);
		MULTIEXTEND_API static float& limit_min(float& src, float min);
		MULTIEXTEND_API static int& limit_min(int& src, int min);

		MULTIEXTEND_API static double& limit_max(double& src, double max);
		MULTIEXTEND_API static float& limit_max(float& src, float max);
		MULTIEXTEND_API static int& limit_max(int& src, int max);

		// transfer Byte size to specific unit output in double
		MULTIEXTEND_API static double ByteSizeTo(int bytesize, SystemSizeUnit unit);

		// transfer Byte size to a proper unit output in double
		MULTIEXTEND_API static std::tuple<const char*, double> ByteSizeConvert(uintmax_t bytesize);
	};
	
}