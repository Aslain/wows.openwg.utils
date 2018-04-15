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
#include <iostream>
#include <fstream>
#include <codecvt>

using std::wcout;
using std::cout;
using std::endl;

using std::cout;

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

std::string readFileUTF8(const std::wstring& filename)
{
	std::wifstream fs(filename);
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

void writeFile(const std::wstring& name, Json::Value &node)
{
	Json::StyledStreamWriter styled("  ");
	std::fstream fs(name, std::ios::out);
	const char BOM[3] = { char(0xEF), char(0xBB), char(0xBF) };

	fs.write(BOM, 3);
	styled.write(fs, node);
	fs.close();
}

std::pair<std::wstring, std::wstring> JsonUtils::GetNamesAndValues(const std::wstring& name, const std::wstring& path)
{
	std::wstringstream names, values;
	std::string file_name, value_path, _path;
	const wchar_t line_break = 13 ;
	Json::Value node;
	Json::Reader reader;

	reader.parse(readFileUTF8(name), node);

	_path = Encoding::wstring_to_utf8(path);

	_path.erase(0, _path.find_first_not_of(' '));
	_path.erase(_path.find_last_not_of(' ') + 1);

	std::vector<std::string> tokens = String::Split(_path, '/');
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
				values << L"arrayValue" << line_break;
				break;
			case Json::ValueType::objectValue:
				values << L"objectValue" << line_break;
				break;
			default:
				values << Encoding::utf8_to_wstring(node[key].asString()) << line_break;
		}
	}
	return std::make_pair(names.str(), values.str());
}

void c_node(const int size, int index, Json::Value &node, const std::vector<std::string>& tokens, Json::Value& value)
{
	if (index <= size)
	{
		Json::ValueType t = node.type();
		for (Json::ValueConstIterator v = node.begin(); v != node.end(); v++)
		{
			std::string key = v.key().asString();
		}
		std::string token = tokens[index].c_str();
		c_node(size, ++index, node[token], tokens, value);
	}
	else
	{
		node.swapPayload(value);
	}
}

bool SetValue(const std::wstring& name, const std::wstring& pathValue, Json::Value& value)
{
	Json::Value node;
	Json::Reader reader;
	reader.parse(readFileUTF8(name), node);
	std::vector<std::string> tokens = String::Split(Encoding::wstring_to_utf8(pathValue), '/');
	try
	{
		int size = tokens.size() - 1;
		int index = 0;
		if (index > size)
		{
			return false;
		}
		c_node(size, index, node, tokens, Json::Value(value));
	}
	catch (Json::LogicError&)
	{
		return false;
	}
	writeFile(name, node);
	return true;
}

bool JsonUtils::SetValueBool(const std::wstring& name, const std::wstring& pathValue, const bool value)
{
	if (!SetValue(name, pathValue, Json::Value(value)))
	{
		return false;
	}
	return true;
}