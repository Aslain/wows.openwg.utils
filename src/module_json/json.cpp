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

#include "json.h"

#include "common/encoding.h"
#include "common/string.h"

#include <string>

Json::Value JsonUtils::ParseString(const std::string& json)
{
    std::string errs;
    std::stringstream input_stream(json);
    Json::Value node;

    Json::parseFromStream(Json::CharReaderBuilder(), input_stream, &node, &errs);

    return node;
}

Json::Value JsonUtils::ParseWString(const std::wstring& json)
{
    return ParseString(Encoding::wstring_to_utf8(json));
}

bool JsonUtils::ContainsKey(const wchar_t* json, const wchar_t* path)
{
    return ContainsKey(std::wstring(json), std::wstring(path));
}

bool JsonUtils::ContainsKey(const std::wstring& json, const std::wstring& path)
{
    Json::Value current_node = ParseWString(json);
    if (current_node.isNull())
    {
        return false;
    }

    std::vector<std::string> tokens = String::Split(Encoding::wstring_to_utf8(path), '/');
    try
    {
        for (unsigned int i = 0; i < tokens.size(); i++)
        {
            current_node = current_node[tokens[i].c_str()];
        }
    }
    catch (Json::LogicError&)
    {
        return false;
    }

    if (current_node.isNull())
        return false;
    else
        return true;
}

std::wstring JsonUtils::GetValue(const wchar_t* json, const wchar_t* path)
{
    return GetValue(std::wstring(json), std::wstring(path));
}

std::wstring JsonUtils::GetValue(const std::wstring& json, const std::wstring& path)
{
    Json::Value current_node = ParseWString(json);
    if(current_node.isNull())
    {
        return std::wstring();
    }

    std::vector<std::string> tokens = String::Split(Encoding::wstring_to_utf8(path), '/');
    try
    {
        for (unsigned int i = 0; i < tokens.size(); i++)
        {
            current_node = current_node[tokens[i].c_str()];
        }
    }
    catch (Json::LogicError&)
    {
        return std::wstring();
    }

    return Encoding::utf8_to_wstring(current_node.asString());
}
