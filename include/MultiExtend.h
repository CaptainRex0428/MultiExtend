#pragma once

//------------------ Base tool ---------------
#include "System/File/File.h"
#include "System/Directory/Directory.h"
#include "System/Operator.h"
#include "System/Hash/HashGenerator.h"

#include "Time/Clock/Clock.h"
#include "Time/Clock/GlobalClock.h"
#include "Time/Timer/Timer.h"

#include "Debug/Message/Message.h"
#include "Debug/Trace/Trace.h"
#include "Debug/Log/Log.h"

#include "MultiExtendDebug.h"

//---------------------------------------------

//----------------- Micro Define --------------
#include "MultiExtendMicro.h"
#include "Debug/Message/MessageMicro.h"
#include "Time/Clock/ClockMicro.h"
#include "Time/Clock/GlobalClockMicro.h"
#include "System/File/FileMicro.h"
#include "System/Directory/DirectoryMicro.h"
#include "Math/MathMicro.h"
#include "Time/Timer/TimerMicro.h"
#include "Debug/Trace/TraceMicro.h"
//---------------------------------------------

namespace MultiExtend
{
	enum InitTag: int
	{
		SDL = 0b00000001,
		openGL = 0b00000010,
		ALL = 0b11111111
	};

	MULTIEXTEND_API int Init(int inttag = ALL);
}

using namespace MultiExtend;