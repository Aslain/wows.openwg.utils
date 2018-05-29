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

#include <cstring>
#include "module_json/json.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

using std::wcout;
using std::cout;
using std::endl;

wchar_t* json = L"{\"Group\": {\"Name\": \"Шаг 1\", \"Description\": \"Сконфигурируйте свой прицел\"}, \"Component\": {\"Name\": \"Установить прицелы\", \"Description\": \"Эти моды заменят стандартный прицел игры!\", \"ID\": \"crosshair_mods\"}, \"Preview\": {\"BMP\": \"sights.bmp\"}}";
wchar_t* path = L"Group/Name";


bool test_1()
{
    std::wstring expected = L"Шаг 1";

    std::wstring result = JsonUtils::GetValue(json, path);

    if (wcscmp(result.c_str(), expected.c_str()) == 0)
        return true;
    else
        return false;
    
}

bool test_2()
{
    if (JsonUtils::ContainsKey(json, path))
        return true;

    return false;
}

bool test_3()
{
    wchar_t* path2 = L"Group/Na2me";
    if (!JsonUtils::ContainsKey(json, path2))
        return true;

    return false;
}

bool test_5(std::wstring name)
{
	std::wstring path_w = L"battle/mirroredVehicleIcons";
	return JsonUtils::SetValueBool(name, path_w, false);
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);
	if (test_1()) 
		wcout << "test_1" << endl;
	if (test_2())
		wcout << "test_2" << endl;
	if (test_3())
		wcout << "test_3" << endl;
	_getch();

    return 0;
}
