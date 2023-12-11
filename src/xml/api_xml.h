// SPDX-License-Identifier: MIT
// Copyright (c) 2023 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

XVMEXT_API_CALL bool __cdecl XML_AddKeyW(_In_ void *object, _In_ const wchar_t *path, _In_ const wchar_t *name, _In_ const wchar_t* value);

XVMEXT_API_CALL bool __cdecl XML_Close(void *object);

XVMEXT_API_CALL bool __cdecl XML_ContainsKeyW(_In_ void *object, _In_ const wchar_t *path);

XVMEXT_API_CALL bool __cdecl XML_ContainsKeyExW(_In_ void *object, _In_ const wchar_t *path, _In_ const wchar_t* value);

XVMEXT_API_CALL void *__cdecl XML_OpenFileW(const wchar_t *path, bool allow_creation);

XVMEXT_API_CALL bool __cdecl XML_SaveFileW(void *object, _In_ const wchar_t *path);

#ifdef __cplusplus
}
#endif
