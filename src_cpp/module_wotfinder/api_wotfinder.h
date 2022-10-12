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
