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

using std::wcout;
using std::endl;


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

std::string readFileUtf8(const std::wstring& file_name)
{
    std::wifstream fs(file_name);
    fs.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
    std::wstringstream wss;
    wss << fs.rdbuf();
    fs.close();

    std::string data = Encoding::wstring_to_utf8(wss.str());
    if ((data[0] == char(0xEF)) && (data[1] == char(0xBB)) && (data[2] == char(0xBF)))
    {
        data.erase(data.begin(), data.begin() + 3);
    }

    return data;
}

void writeFileUtf8(const std::wstring& file_name, Json::Value &node)
{
    Json::StyledStreamWriter styled("  ");
    std::fstream fs(file_name, std::ios::out);
    const char BOM[3] = { char(0xEF), char(0xBB), char(0xBF) };

    fs.write(BOM, 3);
    styled.write(fs, node);
    fs.close();
}

std::pair<std::wstring, std::wstring> getMemberNamesAndValues(Json::Value &node)
{
    const wchar_t line_break = 13;
    std::wstringstream names, values;
    Json::FastWriter fast_write;

    if (!node.isObject() && !node.isArray())
    {
        return std::make_pair(L"", L"");
    }

    std::vector<std::string> keys = node.getMemberNames();
    for (size_t i = 0; i<keys.size(); i++)
    {
        const std::string& key = keys[i];
        names << Encoding::utf8_to_wstring(key) << line_break;
        switch (node[key].type())
        {
        case Json::ValueType::arrayValue:
            //values << L"arrayValue" << line_break;
            //break;
        case Json::ValueType::objectValue:
            values << Encoding::utf8_to_wstring(fast_write.write(node[key]));
            break;
        default:
            values << Encoding::utf8_to_wstring(node[key].asString()) << line_break;
        }
    }
    return std::make_pair(names.str(), values.str());
}

std::pair<std::wstring, std::wstring> JsonUtils::GetNamesAndValues(const std::wstring& file_name, const std::wstring& path)
{
    std::string _path = Encoding::wstring_to_utf8(path);
    Json::Value node;
    Json::Reader reader;

    reader.parse(readFileUtf8(file_name), node);

    std::vector<std::string> tokens = String::Split(String::Trim(_path), '/');
    try
    {
        for (unsigned int i = 0; i < tokens.size(); i++)
        {
            node = node[tokens[i].c_str()];
        }
    }
    catch (Json::LogicError&)
    {
        return std::make_pair(L"", L"");
    }

    return getMemberNamesAndValues(node);
}

std::pair<std::wstring, std::wstring> JsonUtils::GetNamesAndValues(const std::wstring& json)
{
    Json::Value node;
    Json::Reader reader;

    reader.parse(Encoding::wstring_to_utf8(json), node);
    return getMemberNamesAndValues(node);
}

std::wstring JsonUtils::GetArrayValue(const std::wstring& json)
{
    Json::Value node;
    Json::Reader reader;

    reader.parse(Encoding::wstring_to_utf8(json), node);

    if (node.isArray())
    {
        std::wstringstream values;
        const wchar_t line_break = 13;
        Json::FastWriter fast_write;
        Json::ArrayIndex size = node.size();
        for (Json::ArrayIndex i = 0; i < size; ++i)
        {
            switch (node[i].type())
            {
            case Json::ValueType::arrayValue:
            case Json::ValueType::objectValue:
                values << Encoding::utf8_to_wstring(fast_write.write(node[i]));
                break;
            default:
                values << Encoding::utf8_to_wstring(node[i].asString()) << line_break;
            }
        }
        return values.str();
    }
    else
    {
        return json;
    }
}

void c_node(const size_t count, size_t index, Json::Value &node, const std::vector<std::string>& tokens, Json::Value& value)
{
    if (index < count)
    {
        for (Json::ValueConstIterator v = node.begin(); v != node.end(); v++)
        {
            std::string key = v.key().asString();
        }
        std::string token = tokens[index].c_str();
        c_node(count, ++index, node[token], tokens, value);
    }
    else
    {
        node.swapPayload(value);
    }
}

bool SetValue(const std::wstring& file_name, const std::wstring& path_value, Json::Value& value)
{
    Json::Value node;
    Json::Reader reader;
    
    std::vector<std::string> tokens = String::Split(Encoding::wstring_to_utf8(path_value), '/');
    try
    {
        size_t count = tokens.size();
        size_t index = 0;
        if (index >= count)
        {
            return false;
        }
        c_node(count, index, node, tokens, Json::Value(value));
    }
    catch (Json::LogicError&)
    {
        return false;
    }
    writeFileUtf8(file_name, node);
    return true;
}

bool JsonUtils::SetValueBool(const std::wstring& file_name, const std::wstring& path_value, const bool value)
{
    if (!SetValue(file_name, path_value, Json::Value(value)))
    {
        return false;
    }
    return true;
}

void _swapPayload(Json::Value &node, Json::Value &value, bool is_add)
{
    if (node.isObject() && value.isObject())
    {
        Json::Value::Members keys_val = value.getMemberNames();
        size_t const size = keys_val.size();
        for (size_t i = 0; i < size; i++)
        {
            std::string member = keys_val[i];
            if (member.length() > 0)
            {
                if (node.find(member.c_str(), member.c_str() + member.length()) != NULL)
                {
                    _swapPayload(node[member], value[member], is_add);
                }
                else
                {
                    Json::Value::Members keys_node = node.getMemberNames();
                    node[member].swapPayload(value[member]);
                    //node[member].Name = member;
                    //node[member].orderNum = node[keys_node[keys_node.size() - 1]].orderNum + 1;

                }
            }
        }
    }
    else if (node.isArray() && value.isArray() && is_add)
    {
        //Json::Value::Members keys_val = value.getMemberNamesNum();
        size_t const size = value.size();
        for (size_t i = 0; i < size; i++)
        {
            node.append(value[static_cast<Json::ArrayIndex>(i)]);
        }
    }
    else
    {
        node.swapPayload(value);
    }
}

bool JsonUtils::SetValueObj(const std::wstring& file_name, const std::wstring& json, bool is_add)
{
    Json::Value node, value;
    Json::Reader reader;

    try
    {
        reader.parse(readFileUtf8(file_name), node);
        reader.parse(Encoding::wstring_to_utf8(json), value);
        _swapPayload(node, value, is_add);
        writeFileUtf8(file_name, node);
    }
    catch (Json::LogicError&)
    {
        return false;
    }
    return true;
}