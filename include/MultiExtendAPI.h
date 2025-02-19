#pragma once

//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//
//inline void* _malloc(size_t size, const char* filename, int line) {
//	void* ptr = malloc(size);
//
//	char buffer[128] = { 0 };
//	sprintf(buffer, "./memory/%p.memory", ptr);
//
//	FILE* fp = fopen(buffer, "w");
//	fprintf(fp, "[+]addr: %p, filename: %s, line: %d\n", ptr, filename, line);
//
//	fflush(fp);
//	fclose(fp);
//
//	return ptr;
//}
//
//inline void _free(void* ptr, const char* filename, int line) {
//	char buffer[128] = { 0 };
//	sprintf(buffer, "./memory/%p.memory", ptr);
//
//	if (unlink(buffer) < 0) {
//		printf("double free: %p\n", ptr);
//		return;
//	}
//
//	return free(ptr);
//}

//#define malloc(size) _malloc(size,__FILE__,__LINE__)
//#define free(size) _free(size,__FILE__,__LINE__)

#ifdef MULTI_EXTEND_BUILD_DLL_EXPORT
#define MULTIEXTEND_API __declspec(dllexport)
#else
#ifdef MULTI_EXTEND_BUILD_LIB
#define MULTIEXTEND_API
#else
#define MULTIEXTEND_API __declspec(dllimport)
#endif
#endif