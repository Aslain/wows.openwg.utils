/* Copyright (c) 2017-2020, Mikhail Paulyshka.
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

std::string & String::Trim(std::string & str)
{
    return LTrim(RTrim(str));
}

std::string & String::LTrim(std::string & str)
{
    auto it2 = std::find_if(str.begin(), str.end(), [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); });
    str.erase(str.begin(), it2);
    return str;
}

std::string & String::RTrim(std::string & str)
{
    auto it1 = std::find_if(str.rbegin(), str.rend(), [](char ch) { return !std::isspace<char>(ch, std::locale::classic()); });
    str.erase(it1.base(), str.end());
    return str;
}

std::wstring & String::Trim(std::wstring & str)
{
    return LTrim(RTrim(str));
}

std::wstring & String::LTrim(std::wstring & str)
{
    auto it2 = std::find_if(str.begin(), str.end(), [](wchar_t ch) { return !std::isspace<wchar_t>(ch, std::locale::classic()); });
    str.erase(str.begin(), it2);
    return str;
}

std::wstring & String::RTrim(std::wstring & str)
{
    auto it1 = std::find_if(str.rbegin(), str.rend(), [](wchar_t ch) { return !std::isspace<wchar_t>(ch, std::locale::classic()); });
    str.erase(it1.base(), str.end());
    return str;
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
