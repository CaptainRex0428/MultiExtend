#include "Math/Unit.h"

#include <math.h>

double MultiExtend::ByteSizeTo(int bytesize, SystemSizeUnit unit)
{
	// return bytesize / pow(1024, unit);
	return 100;
}

std::tuple<const char*, double> MultiExtend::ByteSizeConvert(uintmax_t bytesize)
{
	double size = (double)bytesize;
	const char* unit = "Byte";

	// to KB
	double sizebuf = size / 1024;
	if (((int)sizebuf) == 0)
	{
		return {unit,size};
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
