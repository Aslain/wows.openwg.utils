// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <string>
#include <vector>

namespace OpenWG::Utils {
    namespace String {

        std::string Trim(const std::string &str);

        std::string LTrim(const std::string &str);

        std::string RTrim(const std::string &str);

        std::wstring Trim(const std::wstring &str);

        std::wstring LTrim(const std::wstring &str);

        std::wstring RTrim(const std::wstring &str);

        std::vector<std::string> Split(const std::string &s, char delim);

        std::vector<std::wstring> Split(const std::wstring &s, wchar_t delim);

        std::vector<std::wstring> Split(const std::wstring &s, wchar_t delim, size_t limit);

        std::wstring Replace(const std::wstring &where, const std::wstring &from, const std::wstring &to);

        std::wstring ReplaceRegex(const std::wstring &where, const std::wstring &from, const std::wstring &to);


        std::wstring Substring(const std::wstring &where, size_t from, size_t to = std::wstring::npos);

        std::wstring VecToWstring(const std::vector<uint8_t> &vec);

        std::wstring ToLower(const std::wstring& str);

    }
}
