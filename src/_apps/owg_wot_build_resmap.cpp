// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2025 OpenWG.Utils Contributors

#include <algorithm>
#include <filesystem>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "wot/api_wot.h"

namespace
{

std::wstring ReadLine(const std::wstring& prompt, bool allowEmpty = false)
{
    std::wstring line;
    while (true)
    {
        std::wcout << prompt;
        if (!std::getline(std::wcin, line))
        {
            std::wcin.clear();
            if (allowEmpty)
            {
                return {};
            }
            continue;
        }

        if (!line.empty() && line.back() == L'\r')
        {
            line.pop_back();
        }

        if (line.empty() && !allowEmpty)
        {
            std::wcout << L"Input cannot be empty. Please try again." << std::endl;
            continue;
        }

        break;
    }
    return line;
}

std::wstring DescribeVendor(int32_t vendor)
{
    switch (vendor)
    {
        case ClientVendor::WoT_Vendor_WG:
            return L"WG";
        case ClientVendor::WoT_Vendor_Lesta:
            return L"Lesta";
        case ClientVendor::WoT_Vendor_Unknown:
        default:
            return L"Unknown";
    }
}

std::wstring DescribeBranch(int32_t branch)
{
    switch (branch)
    {
        case ClientBranch::WoT_Branch_Release:
            return L"Release";
        case ClientBranch::WoT_Branch_CommonTest:
            return L"Common Test";
        case ClientBranch::WoT_Branch_SuperTest:
            return L"Super Test";
        case ClientBranch::WoT_Branch_Sandbox:
            return L"Sandbox";
        case ClientBranch::WoT_Branch_ClosedTest:
            return L"Closed Test";
        case ClientBranch::WoT_Branch_Unknown:
        default:
            return L"Unknown";
    }
}

void PrintClients()
{
    const int32_t count = WOT_GetClientsCount();
    std::wcout << L"Detected clients: " << count << std::endl;

    wchar_t buffer[1024]{};

    for (int32_t idx = 0; idx < count; ++idx)
    {
        WOT_GetClientPathW(buffer, std::size(buffer), idx);
        const std::wstring clientPath(buffer);

        WOT_GetClientVersionW(buffer, std::size(buffer), idx);
        const std::wstring clientVersion(buffer);

        WOT_GetClientRealmW(buffer, std::size(buffer), idx);
        const std::wstring clientRealm(buffer);

        std::wcout << L"[" << idx << L"] " << clientPath << std::endl;
        std::wcout << L"    Version : " << clientVersion << std::endl;
        std::wcout << L"    Vendor  : " << DescribeVendor(WOT_GetClientVendor(idx)) << std::endl;
        std::wcout << L"    Branch  : " << DescribeBranch(WOT_GetClientBranch(idx)) << std::endl;
        std::wcout << L"    Realm   : " << clientRealm << std::endl;
    }
}

int32_t ReadClientIndex(int32_t maxIndex)
{
    while (true)
    {
        const std::wstring input = ReadLine(L"Enter client index: ");
        try
        {
            const long value = std::stol(input);
            if (value < 0 || value >= maxIndex)
            {
                std::wcout << L"Index is out of range. Valid range [0, " << (maxIndex - 1) << L"]." << std::endl;
                continue;
            }
            return static_cast<int32_t>(value);
        }
        catch (const std::exception&)
        {
            std::wcout << L"Invalid number. Please enter a valid integer value." << std::endl;
        }
    }
}

} // namespace

int wmain()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    std::wcout << L"OpenWG.Utils: WoT res_map builder" << std::endl;

    WOT_LauncherRescan();

    const int32_t clientCount = WOT_GetClientsCount();
    if (clientCount <= 0)
    {
        std::wcout << L"No clients detected. Press Enter to exit." << std::endl;
        std::wcin.get();
        return 1;
    }

    PrintClients();
    const int32_t clientIndex = ReadClientIndex(clientCount);

    std::wcout << L"Building res_map.json for selected client..." << std::endl;
    const int32_t result = WOT_ClientBuildResMap(clientIndex);

    if (result == 1)
    {
        std::wcout << L"[OK] res_map.json has been generated successfully." << std::endl;
    }
    else if (result == 0)
    {
        std::wcout << L"[WARN] res_map.json generation completed without changes or no data was available." << std::endl;
    }
    else
    {
        std::wcout << L"[ERROR] Failed to build res_map.json for the selected client." << std::endl;
    }

    std::wcout << L"Press Enter to exit." << std::endl;
    std::wcin.get();
    return result == 1 ? 0 : (result == 0 ? 2 : 3);
}