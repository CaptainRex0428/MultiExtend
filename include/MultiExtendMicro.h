#pragma once

#pragma warning(disable:5103)
#define _MULTIEXTEND_MICRO_CONTACT(x,y) x##y
#define MULTIEXTEND_MICRO_CONTACT(x,y) _MULTIEXTEND_MICRO_CONTACT(x,y)

#define MULTIEXTEND_VNAME(value) (#value)
#define MULTIEXTEND_CNAME(value) (#value)

#define MULTIEXTEND_THREAD_DELAY_MICRO(value) std::this_thread::sleep_for(std::chrono::microseconds(value))

#define MULTIEXTEND_BIT(value) (1 << value)