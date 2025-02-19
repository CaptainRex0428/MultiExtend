#pragma once

#include <stdint.h>

#include "MultiExtendAPI.h"

namespace MultiExtendMath
{
	MULTIEXTEND_API int Clamp(int src, int min = 0, int max = 1);
	MULTIEXTEND_API float Clamp(float src, float min = 0, float max = 1);
	MULTIEXTEND_API uint8_t Clamp(uint8_t src, uint8_t min = 0, uint8_t max = 1);

	MULTIEXTEND_API double& limit_min(double& src, double min);
	MULTIEXTEND_API float& limit_min(float& src, float min);
	MULTIEXTEND_API int& limit_min(int& src, int min);

	MULTIEXTEND_API double& limit_max(double& src, double max);
	MULTIEXTEND_API float& limit_max(float& src, float max);
	MULTIEXTEND_API int& limit_max(int& src, int max);
};