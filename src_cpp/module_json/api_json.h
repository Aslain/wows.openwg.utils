/* Copyright (c) 2017-2021, Mikhail Paulyshka.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

XVMEXT_API_CALL bool __cdecl JSON_ContainsKeyW(_In_ const wchar_t* json, _In_ const wchar_t* path);

XVMEXT_API_CALL void __cdecl JSON_GetValueW(_In_ const wchar_t* json, _In_ const wchar_t* path, _Out_ wchar_t* output, _In_ unsigned int output_size);

XVMEXT_API_CALL void __cdecl JSON_SetValueBoolW(_In_ const wchar_t* file_name, _In_ const wchar_t* path, _In_ const bool value);

XVMEXT_API_CALL void __cdecl JSON_SetValueObjW(_In_ const wchar_t* file_name, _In_ const wchar_t* json, _In_ const bool is_add);

XVMEXT_API_CALL void __cdecl JSON_GetNamesAndValuesW(_In_ const wchar_t* file_name, _In_ const wchar_t* path, _Out_ wchar_t* names, _Out_ wchar_t* values, _In_ unsigned int output_size);

XVMEXT_API_CALL void __cdecl JSON_GetNamesAndValuesW_S(_In_ const wchar_t* json, _Out_ wchar_t* names, _Out_ wchar_t* values, _In_ unsigned int output_size);

XVMEXT_API_CALL void __cdecl JSON_GetArrayValueW_S(_In_ const wchar_t* json, _Out_ wchar_t* output, _In_ unsigned int output_size);

#ifdef __cplusplus
}
#endif
