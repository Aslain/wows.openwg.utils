// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <string>
#include <vector>

class String {
public:
    static std::string Trim(const std::string& str);
    static std::string LTrim(const std::string& str);
    static std::string RTrim(const std::string& str);

    static std::wstring Trim(const std::wstring& str);
    static std::wstring LTrim(const std::wstring& str);
    static std::wstring RTrim(const std::wstring& str);

    static std::vector<std::string> Split(const std::string& s, const char delim);
    static std::vector<std::wstring> Split(const std::wstring& s, const wchar_t delim);
    static std::vector<std::wstring> Split(const std::wstring& s, const wchar_t delim, size_t limit);

    static std::wstring Replace(const std::wstring& where, const std::wstring& from, const std::wstring& to);

    static std::wstring Substring(const std::wstring& where, size_t from, size_t to = std::wstring::npos);


    static std::wstring VecToWstring(const std::vector<uint8_t>& vec);

};;
