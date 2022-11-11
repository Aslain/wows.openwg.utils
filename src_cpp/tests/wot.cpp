// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include <iostream>

#include <io.h>
#include <fcntl.h>

#include "module_wot/api_wot.h"

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    wchar_t buffer[1024]{};

    //WOT_LauncherSetDefault(Launcher_Flavour_Standalone);

    std::wcout << L"WoT clients count   : " << WOT_GetClientsCount() << std::endl;

    std::wcout << L"WoT preferred client (Unknown)   : " << WOT_LauncherGetPreferredClient(Launcher_Flavour_Unknown)
               << std::endl;
    std::wcout << L"WoT preferred client (WG)        : " << WOT_LauncherGetPreferredClient(Launcher_Flavour_WG)
               << std::endl;
    std::wcout << L"WoT preferred client (360)       : " << WOT_LauncherGetPreferredClient(Launcher_Flavour_China360)
               << std::endl;
    std::wcout << L"WoT preferred client (Steam)     : " << WOT_LauncherGetPreferredClient(Launcher_Flavour_Steam)
               << std::endl;
    std::wcout << L"WoT preferred client (Lesta)     : " << WOT_LauncherGetPreferredClient(Launcher_Flavour_Lesta)
               << std::endl;
    std::wcout << L"WoT preferred client (Standalone): " << WOT_LauncherGetPreferredClient(Launcher_Flavour_Standalone)
               << std::endl;
    std::wcout << std::endl;

    for (int i = 0; i < WOT_GetClientsCount(); i++) {

        std::wcout << L"-------------" << std::endl;
        std::wcout << L"Client Index    : " << i << std::endl;
        std::wcout << L"Client Branch   : " << WOT_GetClientBranch(i) << std::endl;

        WOT_GetClientExeVersionW(buffer, std::size(buffer), i);
        std::wcout << L"Client ExeVer   : " << buffer << std::endl;

        WOT_GetClientLocaleW(buffer, std::size(buffer), i);
        std::wcout << L"Client Locale   : " << buffer << std::endl;

        WOT_GetClientPathW(buffer, std::size(buffer), i);
        std::wcout << L"Client Path     : " << buffer << std::endl;

        WOT_GetClientRealmW(buffer, std::size(buffer), i);
        std::wcout << L"Client Realm    : " << buffer << std::endl;


        std::wcout << L"Client Type     : " << WOT_GetClientType(i) << std::endl;
        std::wcout << L"Client Launcher : " << WOT_GetClientLauncherFlavour(i) << std::endl;
        WOT_GetClientVersionW(buffer, std::size(buffer), i);
        std::wcout << L"Client Ver      : " << buffer << std::endl;

        std::wcout << std::endl;
    }
}
