// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

//WOT
XVMEXT_API_CALL int32_t WOT_AddClientA(char* path);
XVMEXT_API_CALL int32_t WOT_AddClientW(wchar_t* path);


XVMEXT_API_CALL void WOT_GetPreferredClientPathA(char* buffer, int32_t buffer_size);
XVMEXT_API_CALL void WOT_GetPreferredClientPathW(wchar_t* buffer, int32_t buffer_size);

XVMEXT_API_CALL int32_t WOT_GetClientsCount();

XVMEXT_API_CALL void WOT_GetClientLocaleW(wchar_t* buffer, int32_t buffer_size, int32_t index);
XVMEXT_API_CALL void WOT_GetClientLocaleA(char* buffer, int32_t buffer_size, int32_t index);

XVMEXT_API_CALL void WOT_GetClientPathW(wchar_t* buffer, int32_t size, int32_t index);
XVMEXT_API_CALL void WOT_GetClientPathA(char* buffer, int32_t size, int32_t index);

XVMEXT_API_CALL void WOT_GetClientVersionW(wchar_t* buffer, int32_t size, int32_t index);
XVMEXT_API_CALL void WOT_GetClientVersionA(char* buffer, int32_t size, int32_t index);

XVMEXT_API_CALL void WOT_GetClientExeVersionW(wchar_t* buffer, int32_t size, int32_t index);
XVMEXT_API_CALL void WOT_GetClientExeVersionA(char* buffer, int32_t size, int32_t index);

// -1- error, 0-unknown, 1-release , 2-ct, 3-st, 4-sandbox
XVMEXT_API_CALL int32_t WOT_GetClientBranch(int32_t index);

// -1- error, 0-unknown, 1-sd , 2-hd
XVMEXT_API_CALL int32_t WOT_GetClientType(int32_t index);

// -1- error, 0-unknown, 1-wg , 2-360, 3-steam, 4-lesta
XVMEXT_API_CALL int32_t WOT_GetClientWgcFlavour(int32_t index);

#ifdef __cplusplus
}
#endif
