// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include <iostream>

#include <io.h>
#include <fcntl.h>

#include "module_wotfinder/api_wotfinder.h"

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    wchar_t buffer[1024]{};


    std::wcout << L"WoT clients count   : " << WOT_GetClientsCount() << std::endl;

    WOT_GetPreferredClientPathW(buffer, std::size(buffer));
    std::wcout << L"WoT preferred client: " << buffer << std::endl << std::endl;

    for (int i = 0; i < WOT_GetClientsCount(); i++)
    {

        std::wcout << L"-------------" << std::endl;
        std::wcout << L"Client Index : " << i << std::endl;
        std::wcout << L"Client Branch: " << WOT_GetClientBranch(i) << std::endl;

        WOT_GetClientExeVersionW(buffer, std::size(buffer), i);
        std::wcout << L"Client ExeVer: " << buffer << std::endl;

        WOT_GetClientLocaleW(buffer, std::size(buffer), i);
        std::wcout << L"Client Locale: " << buffer << std::endl;

        WOT_GetClientPathW(buffer, std::size(buffer), i);
        std::wcout << L"Client Path  : " << buffer << std::endl;

        std::wcout << L"Client Type  : " << WOT_GetClientType(i) << std::endl;
        std::wcout << L"Client WGC F : " << WOT_GetClientWgcFlavour(i) << std::endl;
        WOT_GetClientVersionW(buffer, std::size(buffer), i);
        std::wcout << L"Client Ver   : " << buffer << std::endl;

        std::wcout << std::endl;
    }
    system("pause");
}
