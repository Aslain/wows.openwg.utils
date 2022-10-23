// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

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

wchar_t* json = L"{\"Group\": {\"Name\": \"��� 1\", \"Description\": \"��������������� ���� ������\"}, \"Component\": {\"Name\": \"���������� �������\", \"Description\": \"��� ���� ������� ����������� ������ ����!\", \"ID\": \"crosshair_mods\"}, \"Preview\": {\"BMP\": \"sights.bmp\"}}";
wchar_t* path = L"Group/Name";


bool test_1()
{
    std::wstring expected = L"��� 1";

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
