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

#include "api_wgc.h"

#include "wgc.h"

#include <Windows.h>

#include <locale>
#include <string>

void WGC_GetInstallPathA(char * buffer, int buffer_size)
{
	if (buffer_size <= 0)
	{
		return;
	}

	wchar_t* wbuffer = (wchar_t*)malloc(buffer_size * sizeof(wchar_t));

	if (wbuffer != nullptr)
	{
		WGC_GetInstallPathW(wbuffer, buffer_size);

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

void WGC_GetInstallPathW(wchar_t * buffer, int buffer_size)
{
	if (buffer_size <= 0)
	{
		return;
	}

	std::wstring wgcpath = WGC::GetWGCInstallPath();

	if (!wgcpath.empty())
	{
		wcscpy_s(buffer, buffer_size, wgcpath.c_str());
	}
	else
	{
		buffer[0] = '\0';
	}
}

bool WGC_IsInstalled()
{
	return !WGC::GetWGCInstallPath().empty();
}
