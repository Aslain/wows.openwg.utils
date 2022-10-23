// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <string>

class Registry
{
public:
    static std::wstring GetStringValue(const wchar_t* subkey, const wchar_t* value);
};
