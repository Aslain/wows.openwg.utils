// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

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
