// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

XVMEXT_API_CALL bool __cdecl JSON_OLD_ContainsKeyW(_In_ const wchar_t* json, _In_ const wchar_t* path);

XVMEXT_API_CALL void __cdecl JSON_OLD_GetValueW(_In_ const wchar_t* json, _In_ const wchar_t* path, _Out_ wchar_t* output, _In_ unsigned int output_size);

XVMEXT_API_CALL void __cdecl JSON_OLD_SetValueBoolW(_In_ const wchar_t* file_name, _In_ const wchar_t* path, _In_ const bool value);

XVMEXT_API_CALL void __cdecl JSON_OLD_SetValueObjW(_In_ const wchar_t* file_name, _In_ const wchar_t* json, _In_ const bool is_add);

XVMEXT_API_CALL void __cdecl JSON_OLD_GetNamesAndValuesW(_In_ const wchar_t* file_name, _In_ const wchar_t* path, _Out_ wchar_t* names, _Out_ wchar_t* values, _In_ unsigned int output_size);

XVMEXT_API_CALL void __cdecl JSON_OLD_GetNamesAndValuesW_S(_In_ const wchar_t* json, _Out_ wchar_t* names, _Out_ wchar_t* values, _In_ unsigned int output_size);

XVMEXT_API_CALL void __cdecl JSON_OLD_GetArrayValueW_S(_In_ const wchar_t* json, _Out_ wchar_t* output, _In_ unsigned int output_size);

#ifdef __cplusplus
}
#endif
