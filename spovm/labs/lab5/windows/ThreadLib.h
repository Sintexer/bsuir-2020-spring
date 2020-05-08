#pragma once
#include "pch.h"

#ifdef THREADLIB_EXPORTS
#define THREADLIB_API __declspec(dllexport)
#else
#define THREADLIB_API __declspec(dllimport)
#endif



bool canLeave = false;
const int bsize = 256;

extern "C" THREADLIB_API void fillZero(char* str, int sz);

extern "C" THREADLIB_API DWORD WINAPI inThread(LPVOID buffer);

extern "C" THREADLIB_API  DWORD WINAPI outThread(LPVOID buffer);