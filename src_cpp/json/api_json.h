// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

XVMEXT_API_CALL void *__cdecl JSON_OpenFileW(const wchar_t *path, bool allow_creation);

XVMEXT_API_CALL void *__cdecl JSON_OpenStringW(const wchar_t* value);

XVMEXT_API_CALL bool __cdecl JSON_Close(void *object);

XVMEXT_API_CALL bool __cdecl JSON_SetBoolW(_In_ void *object, _In_ const wchar_t *path, bool value);

XVMEXT_API_CALL bool __cdecl JSON_SetDoubleW(_In_ void *object, _In_ const wchar_t *path, _In_ double value);

XVMEXT_API_CALL bool __cdecl JSON_SetIntegerW(_In_ void *object, _In_ const wchar_t *path, _In_ int32_t value);

XVMEXT_API_CALL bool __cdecl JSON_SetStringW(_In_ void *object, _In_ const wchar_t *path, _In_ const wchar_t *value);


#ifdef __cplusplus
}
#endif
