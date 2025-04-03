#pragma once

#include <stdint.h>
#include <tuple>

#include "MultiExtendAPI.h"

#define NEARZERO_THRESHOLD 0.0001

namespace MultiExtend
{
	enum SystemSizeUnit
	{
		SizeUnitByte = 0,
		SizeUnitKB = 1,
		SizeUnitMB = 2,
		SizeUnitGB = 3,
		SizeUnitTB = 4,
		SizeUnitPB = 5,
		SizeUnitEB = 6,
		SizeUnitZB = 7,
		SizeUnitYB = 8
	};

	
	namespace Math
	{
		MULTIEXTEND_API int Clamp(int src, int min = 0, int max = 1);
		MULTIEXTEND_API float Clamp(float src, float min = 0, float max = 1);
		MULTIEXTEND_API uint8_t Clamp(uint8_t src, uint8_t min = 0, uint8_t max = 1);

		MULTIEXTEND_API double& limit_min(double& src, double min);
		MULTIEXTEND_API float& limit_min(float& src, float min);
		MULTIEXTEND_API int& limit_min(int& src, int min);
		MULTIEXTEND_API size_t& limit_min(size_t& src, size_t min);

		MULTIEXTEND_API double& limit_max(double& src, double max);
		MULTIEXTEND_API float& limit_max(float& src, float max);
		MULTIEXTEND_API int& limit_max(int& src, int max);
		MULTIEXTEND_API size_t& limit_max(size_t& src, size_t max);

		MULTIEXTEND_API bool NearZero(double& src);
		MULTIEXTEND_API bool NearZero(double&& src);
		MULTIEXTEND_API bool NearZero(float& src);
		MULTIEXTEND_API bool NearZero(float&& src);
		

		// transfer Byte size to specific unit output in double
		MULTIEXTEND_API double ByteSizeTo(int bytesize, SystemSizeUnit unit);

		// transfer Byte size to a proper unit output in double
		MULTIEXTEND_API std::tuple<const char*, double> ByteSizeConvert(uintmax_t bytesize);

		MULTIEXTEND_API double DegreeToRadians(double degree);
		MULTIEXTEND_API float DegreeToRadians(float degree);

		MULTIEXTEND_API double RadiansToDegree(double radians);
		MULTIEXTEND_API float RadiansToDegree(float radians);
		
	};
	
}