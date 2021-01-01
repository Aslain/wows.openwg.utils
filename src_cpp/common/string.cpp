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

#include "string.h"

#include <algorithm>
#include <iterator>
#include <locale>
#include <string>
#include <sstream>

std::string String::Trim(const std::string & str)
{
    return LTrim(RTrim(str));
}

std::string String::LTrim(const std::string & str)
{
    std::string result = str;

    auto it2 = std::find_if(result.begin(), result.end(), [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); });
    result.erase(result.begin(), it2);
    return result;
}

std::string String::RTrim(const std::string & str)
{
    std::string result = str;

    auto it1 = std::find_if(result.rbegin(), result.rend(), [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); });
    result.erase(it1.base(), result.end());
    return result;
}

std::wstring String::Trim(const std::wstring & str)
{
    return LTrim(RTrim(str));
}

std::wstring String::LTrim(const std::wstring & str)
{
    std::wstring result = str;

    auto it2 = std::find_if(result.begin(), result.end(), [](wchar_t ch) { return !std::isspace<wchar_t>(ch, std::locale::classic()); });
    result.erase(result.begin(), it2);
    return result;
}

std::wstring String::RTrim(const std::wstring & str)
{
    std::wstring result = str;

    auto it1 = std::find_if(result.rbegin(), result.rend(), [](wchar_t ch) { return !std::isspace<wchar_t>(ch, std::locale::classic()); });
    result.erase(it1.base(), result.end());
    return result;
}

std::vector<std::string> String::Split(const std::string & s, const char delim)
{
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim))
    {
        *(std::back_inserter(elems)++) = item;
    }

    return elems;
}

std::vector<std::wstring> String::Split(const std::wstring & s, const wchar_t delim)
{
    std::vector<std::wstring> elems;
    std::wstringstream ss(s);
    std::wstring item;

    while (std::getline(ss, item, delim))
    {
        *(std::back_inserter(elems)++) = item;
    }

    return elems;
}

std::wstring String::Replace(const std::wstring& where, const std::wstring& from, const std::wstring& to)
{
    if (!where.size() || !from.size()) {
        return std::wstring(where);
    }

    std::wstring result = where;

    size_t index = 0;
    while (true) {
        index = result.find(from, index);
        if (index == std::wstring::npos) {
            break;
        }

        result.replace(index, from.size(), to);

        index += from.size();
    }

    return result;
}

std::wstring String::Substring(const std::wstring& where, size_t from, size_t to)
{
    if (from == to) {
        return std::wstring();
    }
    if (from == std::wstring::npos || from >= where.size()) {
        return std::wstring();
    }
    if (where.empty()) {
        return std::wstring();
    }

    return where.substr(from, to);
}

std::wstring String::VecToWstring(const std::vector<uint8_t>& vec)
{
    std::wstring result;

    switch (vec.size()) {

    case 1:
    {
        int8_t val = 0;
        memcpy(&val, vec.data(), vec.size());
        result = std::to_wstring(val);
        break;
    }
    case 2:
    {
        int16_t val = 0;
        memcpy(&val, vec.data(), vec.size());
        result = std::to_wstring(val);
        break;
    }
    case 3:
    case 4:
    {
        int32_t val = 0;
        memcpy(&val, vec.data(), vec.size());
        result = std::to_wstring(val);
        break;
    }
    case 5:
    case 6:
    case 7:
    case 8:
    {
        int64_t val = 0;
        memcpy(&val, vec.data(), vec.size());
        result = std::to_wstring(val);
        break;
    }
    case 0:
    default:
    {
        result = std::to_wstring(0);
        break;
    }

    }

    return result;
}
