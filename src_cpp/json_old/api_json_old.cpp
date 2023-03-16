// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "json_old/api_json_old.h"

#include "json_old/json_utils.h"

bool JSON_OLD_ContainsKeyW(const wchar_t* json, const wchar_t* path)
{
    return JsonUtils::ContainsKey(json, path);
}

void JSON_OLD_GetValueW(const wchar_t* json, const wchar_t* path, wchar_t* output, unsigned int output_size)
{
    if (output_size <= 0)
        return;
    output[0] = L'\0';

    std::wstring val = JsonUtils::GetValue(json, path);

    if(val.empty())
        return;

    wcscpy_s(output, output_size, val.c_str());
}

void JSON_OLD_SetValueBoolW(const wchar_t* file_name, const wchar_t* path, const bool value)
{
    JsonUtils::SetValueBool(file_name, path, value);
}


void JSON_OLD_SetValueObjW(const wchar_t* file_name, const wchar_t* json, bool is_add)
{
    JsonUtils::SetValueObj(file_name, json, is_add);
}

void JSON_OLD_GetNamesAndValuesW(const wchar_t* file_name, const wchar_t* path, wchar_t* names, wchar_t* values, unsigned int output_size)
{
    if (output_size <= 0)
        return;
    names[0] = L'\0';
    values[0] = L'\0';

    std::pair<std::wstring, std::wstring> val = JsonUtils::GetNamesAndValues(file_name, path);

    if (val.first.empty())
        return;

    wcscpy_s(names, output_size, val.first.c_str());
    wcscpy_s(values, output_size, val.second.c_str());
}

void JSON_OLD_GetNamesAndValuesW_S(const wchar_t* json, wchar_t* names, wchar_t* values, unsigned int output_size)
{
    if (output_size <= 0)
        return;
    names[0] = L'\0';
    values[0] = L'\0';

    std::pair<std::wstring, std::wstring> val = JsonUtils::GetNamesAndValues(json);

    if (val.first.empty())
        return;

    wcscpy_s(names, output_size, val.first.c_str());
    wcscpy_s(values, output_size, val.second.c_str());
}

void JSON_OLD_GetArrayValueW_S(const wchar_t* json, wchar_t* output, unsigned int output_size)
{
    if (output_size <= 0)
        return;
    output[0] = L'\0';

    std::wstring val = JsonUtils::GetArrayValue(json);

    if (val.empty())
        return;

    wcscpy_s(output, output_size, val.c_str());
}