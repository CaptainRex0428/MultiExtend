#pragma once

#ifdef MULTI_EXTEND_BUILD_DLL_EXPORT
#define MULTIEXTEND_API __declspec(dllexport)
#else
#ifdef MULTI_EXTEND_BUILD_LIB
#define MULTIEXTEND_API
#else
#define MULTIEXTEND_API __declspec(dllimport)
#endif
#endif