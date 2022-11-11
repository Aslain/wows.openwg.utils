// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include <array>
#include <algorithm>
#include <filesystem>
#include <iostream>

#include <Windows.h>


#include "common/filesystem.h"
#include "module_wine/wine.h"

/*
int WotDetector::AddClient(std::wstring directory, LauncherFlavour flavour)
{
    if (directory.empty())
        return -1;

    if (directory.back() != *L"\\")
        directory.append(L"\\");

    auto exists = [&](const std::wstring &s) {
        return std::find_if(
            begin(WotDetector::clients),
            end(WotDetector::clients),
            [&](WotClient &f) {
                std::wstring path_1 = f.GetPath();
                std::transform(path_1.begin(), path_1.end(), path_1.begin(), ::tolower);

                std::wstring path_2 = s;
                std::transform(path_2.begin(), path_2.end(), path_2.begin(), ::tolower);

                return path_1 == path_2;
            });
    };

    auto dir_it = exists(directory);

    if (dir_it!=WotDetector::clients.end())
        return std::distance(WotDetector::clients.begin(), dir_it);


    WotClient client(directory, flavour);
    if (client.IsValid())
    {
        WotDetector::clients.push_back(client);
        return WotDetector::clients.size() - 1;
    }
    else
    {
        return -1;
    }
}
*/