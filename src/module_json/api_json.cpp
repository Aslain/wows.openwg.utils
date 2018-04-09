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

#include "api_json.h"

#include "json.h"

bool JSON_ContainsKeyW(const wchar_t* json, const wchar_t* path)
{
    return JsonUtils::ContainsKey(json, path);
}

void JSON_GetValueW(const wchar_t* json, const wchar_t* path, wchar_t* output, unsigned int output_size)
{ 
    if (output_size <= 0)
        return;
    output[0] = L'\0';

    std::wstring val = JsonUtils::GetValue(json, path);

    if(val.empty())
        return;

    wcscpy_s(output, output_size, val.c_str());
}

void JSON_SetValueBoolW(const wchar_t* name, const wchar_t* path, const bool value)
{
	JsonUtils::SetValueBool(name, path, value);
}

void JSON_GetSettingsConfigW(const wchar_t* name, wchar_t* output, unsigned int output_size)
{
	if (output_size <= 0)
		return;
	output[0] = L'\0';

	std::wstring val = JsonUtils::GetSettingsConfig(name);

	if (val.empty())
		return;

	wcscpy_s(output, output_size, val.c_str());
}