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

std::wstring JsonUtils::SetValue(const wchar_t* json, const wchar_t* path, const wchar_t* value)
{
	return SetValue(std::wstring(json), std::wstring(path), std::wstring(value));
}


void c_node(int index, Json::Value& node, const std::vector<std::string>& tokens, const std::wstring& value)
{
	if (index > 0)
	{
		c_node(index - 1, node[tokens[index].c_str()], tokens, value);
	}
	else
	{
		node = Encoding::wstring_to_utf8(value);
	}
}

std::wstring JsonUtils::SetValue(const std::wstring& json, const std::wstring& path, const std::wstring& value)
{
	Json::Value node = ParseWString(json);
	if (node.isNull())
	{
		return json;
	}
	std::vector<std::string> tokens = String::Split(Encoding::wstring_to_utf8(path), '/');
	try
	{
		int index = tokens.size() - 1;
		if (index < 0)
		{
			return json;
		}
		c_node(index, node, tokens, value);
	}
	catch (Json::LogicError&)
	{
		return json;
	}
	Json::StyledWriter styled;
	std::string str = styled.write(node);
	//std::string str = node.toStyledString();
	
	std::wstring wstr = Encoding::utf8_to_wstring(str);

	//Json::StyledStreamWriter styledStream;
	//styledStream.write(cout, node);
	return wstr;
}

void c_node(const int size, int index, Json::Value &node, const std::vector<std::string>& tokens, const bool& value)
{
	if (index <= size)
	{
		Json::ValueType t = node.type();
		for (Json::ValueConstIterator v = node.begin(); v != node.end(); v++)
		{
			std::string key = v.key().asString();
		}
		std::string token = tokens[index].c_str();
		//Json::Value children = node[token];
		c_node(size, ++index, node[token], tokens, value);
	}
	else
	{
		Json::Value new_value = value;
		node.swapPayload(new_value);
	}
}

std::wstring readFileUTF8(const std::wstring& filename)
{
	std::wifstream wif(filename);
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstringstream wss;
	wss << wif.rdbuf();
	wif.close();
	return wss.str();
}

bool JsonUtils::SetValueF(const std::wstring& name, const std::wstring& path, const bool value)
{
	std::string data = Encoding::wstring_to_utf8(readFileUTF8(name));

	if ((data[0] == char(0xEF)) && (data[1] == char(0xBB)) && (data[2] == char(0xBF)))
	{
		data = data.erase(0, 3);
	}

	Json::Value node;
	Json::Reader reader;
	reader.parse(data, node); 

	//for (Json::ValueConstIterator v = node.begin(); v != node.end(); v++)
	//{
	//	std::string key = v.key().asString();
	//}

	std::vector<std::string> tokens = String::Split(Encoding::wstring_to_utf8(path), '/');
	try
	{
		int size = tokens.size() - 1;
		int index = 0;
		if (index > size)
		{
			return false;
		}
		c_node(size, index, node, tokens, value);
	}
	catch (Json::LogicError&)
	{
		return false;
	}

	Json::StyledStreamWriter styled;
	std::fstream fs(L"d:\\My\\Programming\\InnoSetup\\extensions\\src_tests\\conf\\battle1.xc", std::ios::out);

	const char BOM[3] = { 0xEF, 0xBB, 0xBF };

	fs.write(BOM, 3);
	styled.write(fs, node);
	fs.close();

	return true;

}