// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "registry.h"

#include <Windows.h>

std::wstring Registry::GetStringValue(const wchar_t* subkey, const wchar_t* value)
{
    HKEY hKey = 0;
    wchar_t val[1024] { 0 };
    DWORD value_length = 1024;

    if (RegOpenKeyW(HKEY_CURRENT_USER, subkey, &hKey) != ERROR_SUCCESS)
    {
        if(RegOpenKeyW(HKEY_LOCAL_MACHINE, subkey, &hKey) != ERROR_SUCCESS)
        {
            return std::wstring();
        }
    }

    if (RegQueryValueExW(hKey, value, nullptr, nullptr, (LPBYTE)&val, &value_length) != ERROR_SUCCESS)
    {
        return std::wstring();
    }

    return std::wstring(val);
}
