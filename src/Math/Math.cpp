#include "Math/Math.h"

int MultiExtendMath::Clamp(int src, int min, int max)
{
	if (src <= min)
	{
		return min;
	}

	if (src >= max)
	{
		return max;
	}

	return src;
}

float MultiExtendMath::Clamp(float src, float min, float max)
{
	if (src <= min)
	{
		return min;
	}

	if (src >= max)
	{
		return max;
	}

	return src;
}

uint8_t MultiExtendMath::Clamp(uint8_t src, uint8_t min, uint8_t max)
{
	if (src <= min)
	{
		return min;
	}

	if (src >= max)
	{
		return max;
	}

	return src;
}

double& MultiExtendMath::limit_min(double& src, double min)
{
	if (src < min)
	{
		src = min;
	}

	return src;
}

float& MultiExtendMath::limit_min(float& src, float min)
{
	if (src < min)
	{
		src = min;
	}

	return src;
}

int& MultiExtendMath::limit_min(int& src, int min)
{
	if (src < min)
	{
		src = min;
	}

	return src;
}

double& MultiExtendMath::limit_max(double& src, double max)
{
	if (src > max)
	{
		src = max;
	}

	return src;
}

float& MultiExtendMath::limit_max(float& src, float max)
{
	if (src > max)
	{
		src = max;
	}

	return src;
}

int& MultiExtendMath::limit_max(int& src, int max)
{
	if (src > max)
	{
		src = max;
	}

	return src;
}