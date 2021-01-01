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

#include "wine.h"

#include <Windows.h>
#include <iostream>

WineStatus Wine::GetStatus()
{
    typedef char *(__cdecl *t_wine_get_build_id)(void);
    typedef void (__cdecl *t_wine_get_host_version)(const char **sysname, const char **release );

    WineStatus st{};

    const HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if(ntdll != nullptr)
    {
        if (GetProcAddress(ntdll, "wine_server_call") != nullptr) {
            st.running_on = true;
        }

        const auto wine_get_build_id = t_wine_get_build_id(GetProcAddress(ntdll, "wine_get_version"));
        if (wine_get_build_id != nullptr)
        {
            char* build = wine_get_build_id();
            st.build = new wchar_t[strlen(build) + 1]{};
            mbstowcs(st.build, build, strlen(build));
        }

        const auto wine_get_host_version = t_wine_get_host_version(GetProcAddress(ntdll, "wine_get_host_version"));
        if (wine_get_host_version != nullptr)
        {
            const char* sys = nullptr;
            const char* rel = nullptr;
            wine_get_host_version(&sys, &rel);

            if (sys != nullptr)
            {
                st.system = new wchar_t[strlen(sys) + 1]{};
                mbstowcs(st.system, sys, strlen(sys));
            }

            if (rel != nullptr)
            {
                st.release = new wchar_t[strlen(rel) + 1]{};
                mbstowcs(st.release, rel, strlen(rel));
            }
        }
    }

    return st;
}
