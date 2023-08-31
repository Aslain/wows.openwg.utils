// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Encoding
{
public:
    // convert UTF-8 string to wstring
    static std::wstring utf8_to_wstring(const std::string& str);

    // convert wstring to UTF-8 string
    static std::string wstring_to_utf8(const std::wstring& str);

    // convert vector of chars to Base64 wide string
    static std::wstring vec_to_base64w(const std::vector<uint8_t>& vec);
};