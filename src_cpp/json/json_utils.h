// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include "api_json.h"

#include <string>

#include <json/json.h>

#include <iostream>
#include <fstream>
#include <codecvt>

class JsonUtils
{
public:
    static Json::Value ParseString(const std::string& json);
    static Json::Value ParseWString(const std::wstring& json);

    static bool ContainsKey(const wchar_t* json, const wchar_t* path);
    static bool ContainsKey(const std::wstring&  json, const std::wstring& path);

    static std::wstring GetValue(const wchar_t* json, const wchar_t* path);
    static std::wstring GetValue(const std::wstring& json, const std::wstring& path);

    static bool SetValueBool(const std::wstring& file_name, const std::wstring& path, const bool value);

    static bool SetValueObj(const std::wstring& file_name, const std::wstring& json, bool is_add);

    static std::pair<std::wstring, std::wstring> GetNamesAndValues(const std::wstring& file_name, const std::wstring& path);
    static std::pair<std::wstring, std::wstring> GetNamesAndValues(const std::wstring& json);

    static std::wstring GetArrayValue(const std::wstring& json);

};