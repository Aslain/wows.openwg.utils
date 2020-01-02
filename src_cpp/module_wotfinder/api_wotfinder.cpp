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

#include "api_wotfinder.h"

#include "wotfinder.h"

#include <Windows.h>

#include <locale>
#include <codecvt>
#include <string>

int WOT_AddClientA(char * path)
{
    if (!WotDetector::IsInitialized())
    {
        WotDetector::FindClients();
    }

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return WotDetector::AddClient(converter.from_bytes(path));
}

int WOT_AddClientW(wchar_t * path)
{
    if (!WotDetector::IsInitialized())
    {
        WotDetector::FindClients();
    }

    return WotDetector::AddClient(std::wstring(path));
}


void WOT_GetPreferredClientPathW(wchar_t *buffer, int32_t buffer_size)
{
    if (buffer_size <= 0)
    {
        return;
    }

    if (!WotDetector::IsInitialized())
    {
        WotDetector::FindClients();
    }

    if (WotDetector::clients.size() > 0)
    {
        wcscpy_s(buffer, buffer_size, WotDetector::clients[0].GetPath().c_str());
    }
    else
    {
        buffer[0] = '\0';
    }
}

void WOT_GetPreferredClientPathA(char *buffer, int32_t buffer_size)
{
    if (buffer_size <= 0)
    {
        return;
    }

    wchar_t* wbuffer = (wchar_t*)malloc(buffer_size * sizeof(wchar_t));

    if (wbuffer != nullptr)
    {
        WOT_GetPreferredClientPathW(wbuffer, buffer_size);

        WideCharToMultiByte(
            CP_ACP,
            0,
            wbuffer,
            buffer_size * sizeof(wchar_t),
            buffer,
            buffer_size * sizeof(char),
            NULL,
            NULL);

        free(wbuffer);
    }
}

int32_t WOT_GetClientsCount()
{
    if (!WotDetector::IsInitialized())
    {
        WotDetector::FindClients();
    }

    return WotDetector::clients.size();
}

void WOT_GetClientLocaleW(wchar_t * buffer, int32_t buffer_size, int32_t index)
{
    if (buffer_size <= 0)
    {
        return;
    }

    if (!WotDetector::IsInitialized())
    {
        WotDetector::FindClients();
    }

    if (WotDetector::clients.size() > index)
    {
        wcscpy_s(buffer, buffer_size, WotDetector::clients[index].GetClientLocale().c_str());
    }
    else
    {
        buffer[0] = '\0';
    }
}

void WOT_GetClientLocaleA(char * buffer, int32_t buffer_size, int32_t index)
{
    if (buffer_size <= 0)
    {
        return;
    }

    wchar_t* wbuffer = (wchar_t*)malloc(buffer_size * sizeof(wchar_t));
    if (wbuffer != nullptr)
    {
        WOT_GetClientLocaleW(wbuffer, buffer_size, index);

        WideCharToMultiByte(
            CP_ACP,
            0,
            wbuffer,
            buffer_size * sizeof(wchar_t),
            buffer,
            buffer_size * sizeof(char),
            NULL,
            NULL);

        free(wbuffer);
    }
}

void WOT_GetClientPathW(wchar_t *buffer, int32_t buffer_size, int32_t index)
{
    if (buffer_size <= 0)
    {
        return;
    }

    if (!WotDetector::IsInitialized())
    {
        WotDetector::FindClients();
    }

    if (WotDetector::clients.size() > index)
    {
        wcscpy_s(buffer, buffer_size, WotDetector::clients[index].GetPath().c_str());
    }
    else
    {
        buffer[0] = '\0';
    }
}

void WOT_GetClientPathA(char *buffer, int32_t buffer_size, int32_t index)
{
    if (buffer_size <= 0)
    {
        return;
    }

    wchar_t* wbuffer = (wchar_t*)malloc(buffer_size * sizeof(wchar_t));
    if (wbuffer != nullptr)
    {
        WOT_GetClientPathW(wbuffer, buffer_size, index);

        WideCharToMultiByte(
            CP_ACP,
            0,
            wbuffer,
            buffer_size * sizeof(wchar_t),
            buffer,
            buffer_size * sizeof(char),
            NULL,
            NULL);

        free(wbuffer);
    }
}

void WOT_GetClientVersionW(wchar_t *buffer, int32_t buffer_size, int32_t index)
{
    if (buffer_size <= 0)
    {
        return;
    }

    if (!WotDetector::IsInitialized())
    {
        WotDetector::FindClients();
    }

    if (WotDetector::clients.size() > index)
    {
        wcscpy_s(buffer, buffer_size, WotDetector::clients[index].GetClientVersion().c_str());
    }
    else
    {
        buffer[0] = '\0';
    }
}

void WOT_GetClientVersionA(char *buffer, int32_t buffer_size, int32_t index)
{
    if (buffer_size <= 0)
    {
        return;
    }

    wchar_t* wbuffer = (wchar_t*)malloc(buffer_size * sizeof(wchar_t));
    if (wbuffer != nullptr)
    {
        WOT_GetClientVersionW(wbuffer, buffer_size, index);

        WideCharToMultiByte(
            CP_ACP,
            0,
            wbuffer,
            buffer_size * sizeof(wchar_t),
            buffer,
            buffer_size * sizeof(char),
            NULL,
            NULL);

        free(wbuffer);
    }
}

void WOT_GetClientExeVersionW(wchar_t *buffer, int32_t buffer_size, int32_t index)
{
    if (buffer_size <= 0)
    {
        return;
    }

    if (!WotDetector::IsInitialized())
    {
        WotDetector::FindClients();
    }

    if (WotDetector::clients.size() > index)
    {
        wcscpy_s(buffer, buffer_size, WotDetector::clients[index].GetClientExeVersion().c_str());
    }
    else
    {
        buffer[0] = '\0';
    }
}

void WOT_GetClientExeVersionA(char *buffer, int32_t buffer_size, int32_t index)
{
    if (buffer_size <= 0)
    {
        return;
    }

    wchar_t* wbuffer = (wchar_t*)malloc(buffer_size * sizeof(wchar_t));
    if (wbuffer != nullptr)
    {
        WOT_GetClientExeVersionW(wbuffer, buffer_size, index);

        WideCharToMultiByte(
            CP_ACP,
            0,
            wbuffer,
            buffer_size * sizeof(wchar_t),
            buffer,
            buffer_size * sizeof(char),
            NULL,
            NULL);

        free(wbuffer);
    }
}

int32_t WOT_GetClientBranch(int32_t index)
{
    if (!WotDetector::IsInitialized())
    {
        WotDetector::FindClients();
    }

    if (WotDetector::clients.size() > index)
    {
        return WotDetector::clients[index].GetClientBranch();
    }
    else
    {
        return -1;
    }
}

int32_t WOT_GetClientType(int32_t index)
{
    if (!WotDetector::IsInitialized())
    {
        WotDetector::FindClients();
    }

    if (WotDetector::clients.size() > index)
    {
        return WotDetector::clients[index].GetClientType();
    }
    else
    {
        return -1;
    }
}
