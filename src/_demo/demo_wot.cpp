// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include <iostream>
#include <string>

#include <io.h>
#include <fcntl.h>

#include "wot/api_wot.h"

std::wstring describe_client_branch(int32_t branch){
    switch(branch) {
        case ClientBranch::WoT_Branch_Unknown:
            return L"unknown";
        case ClientBranch::WoT_Branch_Release:
            return L"release";
        case ClientBranch::WoT_Branch_CommonTest:
            return L"common test";
        case ClientBranch::WoT_Branch_SuperTest:
            return L"super test";
        case ClientBranch::WoT_Branch_Sandbox:
            return L"sandbox";
        default:
            return std::to_wstring(branch);
    }
}

std::wstring describe_client_type(int32_t type){
    switch(type) {
        case ClientType::WoT_Type_Unknown:
            return L"unknown";
        case ClientType::WoT_Type_SD:
            return L"SD";
        case ClientType::WoT_Type_HD:
            return L"HD";
        default:
            return std::to_wstring(type);
    }
}

std::wstring describe_launcher_flavour(int32_t flavour){
    switch(flavour) {
        case LauncherFlavour::Launcher_Flavour_Unknown:
            return L"unknown";
        case LauncherFlavour::Launcher_Flavour_WG:
            return L"WG";
        case LauncherFlavour::Launcher_Flavour_China360:
            return L"360";
        case LauncherFlavour::Launcher_Flavour_Steam:
            return L"Steam";
        case LauncherFlavour::Launcher_Flavour_Lesta:
            return L"Lesta";
        case LauncherFlavour::Launcher_Flavour_Standalone:
            return L"Standalone";
        default:
            return std::to_wstring(flavour);
    }
}

int main() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    wchar_t buffer[1024]{};

    std::wstring version_pattern{L"1.21.1.*"};

    //WOT_LauncherSetDefault(Launcher_Flavour_Standalone);

    std::wcout << L"WoT version pattern              :" << version_pattern << std::endl;

    std::wcout << L"WoT clients count                : " << WOT_GetClientsCount() << std::endl;

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
        std::wcout << L"Client Index        : " << i << std::endl;

        WOT_GetClientPathW(buffer, std::size(buffer), i);
        std::wcout << L"Client Path         : " << buffer << std::endl;

        WOT_GetClientPathModsW(buffer, std::size(buffer), i);
        std::wcout << L"Client Path Mods    : " << buffer << std::endl;

        WOT_GetClientPathResmodsW(buffer, std::size(buffer), i);
        std::wcout << L"Client Path Resmods : " << buffer << std::endl;

        std::wcout << L"Client Launcher     : " << describe_launcher_flavour(WOT_GetClientLauncherFlavour(i)) << std::endl;
        std::wcout << L"Client Branch       : " << describe_client_branch(WOT_GetClientBranch(i)) << std::endl;
        std::wcout << L"Client Type         : " << describe_client_type(WOT_GetClientType(i)) << std::endl;

        WOT_GetClientRealmW(buffer, std::size(buffer), i);
        std::wcout << L"Client Realm        : " << buffer << std::endl;

        WOT_GetClientLocaleW(buffer, std::size(buffer), i);
        std::wcout << L"Client Locale       : " << buffer << std::endl;

        WOT_GetClientVersionW(buffer, std::size(buffer), i);
        std::wcout << L"Client Ver Client   : " << buffer << std::endl;

        WOT_GetClientExeVersionW(buffer, std::size(buffer), i);
        std::wcout << L"Client Ver Exe      : " << buffer << std::endl;

        std::wcout << L"Client Started      : " << WOT_ClientIsStarted(i) << std::endl;
        std::wcout << L"Client Terminated   : " << WOT_ClientTerminate(i) << std::endl;

        std::wcout << L"Version match       : " << WOT_ClientIsVersionMatch(i, version_pattern.c_str()) << std::endl;

        std::wcout << std::endl;
    }

    std::wcin.get();
}
