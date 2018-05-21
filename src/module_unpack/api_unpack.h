#pragma once

#define API_VERSION_UNPACK 1

#ifdef BUILD_UNPACK
#define API_CALL_UNPACK __declspec(dllexport)
#else
#define API_CALL_UNPACK __declspec(dllimport)
#endif

#include <sal.h>
#include <windows.h>

extern "C" API_CALL_UNPACK unsigned char __cdecl UNPACK_divide(_In_ const wchar_t* path, _In_ const wchar_t* filename);