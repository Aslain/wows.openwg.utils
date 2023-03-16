// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

XVMEXT_API_CALL void* __cdecl JSON_FileOpenW(const wchar_t* path, bool allow_creation);

XVMEXT_API_CALL bool __cdecl JSON_FileClose(void* object);

XVMEXT_API_CALL bool __cdecl JSON_SetBoolW( _In_ void* object, _In_ const wchar_t* path, bool value);

#ifdef __cplusplus
}
#endif
