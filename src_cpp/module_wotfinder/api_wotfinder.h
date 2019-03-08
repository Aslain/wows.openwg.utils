/* Copyright (c) 2017, Mikhail Paulyshka
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

#define API_VERSION_WOTFINDER 5

#ifdef BUILD_WOTFINDER
#define API_CALL_WOTFINDER __declspec(dllexport)
#else
#define API_CALL_WOTFINDER __declspec(dllimport)
#endif

//WOT
extern "C" API_CALL_WOTFINDER int __cdecl WOT_AddClientA(char *path);
extern "C" API_CALL_WOTFINDER int __cdecl WOT_AddClientW(wchar_t *path);


extern "C" API_CALL_WOTFINDER void __cdecl WOT_GetPreferredClientPathA(char *buffer, int buffer_size);
extern "C" API_CALL_WOTFINDER void __cdecl WOT_GetPreferredClientPathW(wchar_t *buffer, int buffer_size);

extern "C" API_CALL_WOTFINDER int  __cdecl WOT_GetClientsCount();

extern "C" API_CALL_WOTFINDER void __cdecl WOT_GetClientLocaleW(wchar_t *buffer, int buffer_size, unsigned int index);
extern "C" API_CALL_WOTFINDER void __cdecl WOT_GetClientLocaleA(char *buffer, int buffer_size, unsigned int index);

extern "C" API_CALL_WOTFINDER void __cdecl WOT_GetClientPathW(wchar_t *buffer, int size, unsigned int index);
extern "C" API_CALL_WOTFINDER void __cdecl WOT_GetClientPathA(char *buffer, int size, unsigned int index);

extern "C" API_CALL_WOTFINDER void __cdecl WOT_GetClientVersionW(wchar_t *buffer, int size, unsigned int index);
extern "C" API_CALL_WOTFINDER void __cdecl WOT_GetClientVersionA(char *buffer, int size, unsigned int index);

extern "C" API_CALL_WOTFINDER void __cdecl WOT_GetClientExeVersionW(wchar_t *buffer, int size, unsigned int index);
extern "C" API_CALL_WOTFINDER void __cdecl WOT_GetClientExeVersionA(char *buffer, int size, unsigned int index);

// -1- error, 0-unknown, 1-release , 2-ct, 3-st, 4-sandbox
extern "C" API_CALL_WOTFINDER int  __cdecl WOT_GetClientBranch(unsigned int index);

// -1- error, 0-unknown, 1-sd , 2-hd
extern "C" API_CALL_WOTFINDER int  __cdecl WOT_GetClientType(unsigned int index);
