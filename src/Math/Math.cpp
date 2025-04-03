#include "Math/Math.h"

#include <cmath>

#undef PI
#define PI 3.141592653589793238462643383279502884

int MultiExtend::Math::Clamp(int src, int min, int max)
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

float MultiExtend::Math::Clamp(float src, float min, float max)
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

uint8_t MultiExtend::Math::Clamp(uint8_t src, uint8_t min, uint8_t max)
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

double& MultiExtend::Math::limit_min(double& src, double min)
{
	if (src < min)
	{
		src = min;
	}

	return src;
}

float& MultiExtend::Math::limit_min(float& src, float min)
{
	if (src < min)
	{
		src = min;
	}

	return src;
}

int& MultiExtend::Math::limit_min(int& src, int min)
{
	if (src < min)
	{
		src = min;
	}

	return src;
}

size_t& MultiExtend::Math::limit_min(size_t& src, size_t min)
{
	if (src < min)
	{
		src = min;
	}

	return src;
}

double& MultiExtend::Math::limit_max(double& src, double max)
{
	if (src > max)
	{
		src = max;
	}

	return src;
}

float& MultiExtend::Math::limit_max(float& src, float max)
{
	if (src > max)
	{
		src = max;
	}

	return src;
}

int& MultiExtend::Math::limit_max(int& src, int max)
{
	if (src > max)
	{
		src = max;
	}

	return src;
}

size_t& MultiExtend::Math::limit_max(size_t& src, size_t max)
{
	if (src > max)
	{
		src = max;
	}

	return src;
}

bool MultiExtend::Math::NearZero(double& src)
{
	return NearZero(std::move(src));
}

bool MultiExtend::Math::NearZero(double&& src)
{
	return std::abs(src) < 0.0001;
}

bool MultiExtend::Math::NearZero(float& src)
{
	return NearZero(std::move(src));
}

bool MultiExtend::Math::NearZero(float&& src)
{
	return NearZero(double(src));
}

double MultiExtend::Math::ByteSizeTo(int bytesize, SystemSizeUnit unit)
{
	// return bytesize / pow(1024, unit);
	return 100;
}

std::tuple<const char*, double> MultiExtend::Math::ByteSizeConvert(uintmax_t bytesize)
{
	double size = (double)bytesize;
	const char* unit = "Byte";

	// to KB
	double sizebuf = size / 1024;
	if (((int)sizebuf) == 0)
	{
		return { unit,size };
	}
	size = sizebuf;
	unit = "KB";

	// to MB
	sizebuf = size / 1024;
	if (((int)sizebuf) == 0)
	{
		return { unit,size };
	}
	size = sizebuf;
	unit = "MB";

	// to GB
	sizebuf = size / 1024;
	if (((int)sizebuf) == 0)
	{
		return { unit,size };
	}
	size = sizebuf;
	unit = "GB";

	// to TB
	sizebuf = size / 1024;
	if (((int)sizebuf) == 0)
	{
		return { unit,size };
	}
	size = sizebuf;
	unit = "TB";

	// to PB
	sizebuf = size / 1024;
	if (((int)sizebuf) == 0)
	{
		return { unit,size };
	}
	size = sizebuf;
	unit = "PB";

	// to EB
	sizebuf = size / 1024;
	if (((int)sizebuf) == 0)
	{
		return { unit,size };
	}
	size = sizebuf;
	unit = "EB";

	// to ZB
	sizebuf = size / 1024;
	if (((int)sizebuf) == 0)
	{
		return { unit,size };
	}
	size = sizebuf;
	unit = "PB";

	return { unit,size };
}

double MultiExtend::Math::DegreeToRadians(double degree)
{
	return degree * 2 * PI / 360;
}

float MultiExtend::Math::DegreeToRadians(float degree)
{
	return (float)DegreeToRadians((double)degree);
}

double MultiExtend::Math::RadiansToDegree(double radians)
{
	return (radians * 360) / (2 * PI);
}

float MultiExtend::Math::RadiansToDegree(float radians)
{
	return (float)RadiansToDegree((double)radians);
}
