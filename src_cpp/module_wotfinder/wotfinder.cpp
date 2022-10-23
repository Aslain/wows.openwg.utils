// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include <array>
#include <algorithm>
#include <filesystem>
#include <iostream>

#include <Windows.h>

#include "wotfinder.h"

#include "common/filesystem.h"
#include "module_wine/wine.h"
#include "module_wgc/wgc_finder.h"
#include "wotlauncher.h"

bool WotDetector::isInitialized = false;
std::vector<WotClient> WotDetector::clients;

void WotDetector::FindClients()
{
    // WGC
    auto wgc_clients = WgcFinder::GetWgcClients();
    for(auto& wgc_client: wgc_clients){
        WotDetector::AddClient(wgc_client.GetClientPreferredPath(), wgc_client.GetFlavour());

        for (auto& path : wgc_client.GetClientPaths()) {
            WotDetector::AddClient(path, wgc_client.GetFlavour());
        }
    }

    // Legacy
    for (auto& path : WotLauncher::GetWotPaths()) {
        WotDetector::AddClient(path);
    }

    // DRIVE:\Games\World_of_Tanks*
    std::vector<std::wstring> pathes{L"", L"Games\\", L"Games\\Wargaming.net\\"};
    std::vector<std::wstring> drives = Filesystem::GetLogicalDrives();

    // Non-windows additions
    WineStatus wine_status = Wine::GetStatus();
    if(wine_status.running_on)
    {
        std::array<wchar_t, 256> buf;
        GetEnvironmentVariableW(L"USERNAME", buf.data(), 256);

        if (wcscmp(wine_status.system, L"Linux")==0)
        {
            // /media/<USERNAME>/ mounted partitions
            std::wstring linux_mounts(std::wstring(L"Z:\\media\\") + std::wstring(buf.data()) + std::wstring(L"\\"));
            if (Filesystem::Exists(linux_mounts))
            {
                for (auto& p : std::filesystem::directory_iterator(linux_mounts))
                {
                    if (!std::filesystem::is_directory(p))
                        continue;

                    drives.push_back(p.path().wstring()+L"\\");
                }
            }
        }

        if (wcscmp(wine_status.system, L"Darwin")==0)
        {
            // /Volumes/ mounted partitions
            if (Filesystem::Exists(L"Z:\\Volumes\\"))
            {
                for (auto& p : std::filesystem::directory_iterator(L"Z:\\Volumes\\"))
                {
                    if (!std::filesystem::is_directory(p))
                        continue;

                    drives.push_back(p.path().wstring() + L"\\");
                }
            }
        }

        // WoT OSX edition (Wargaming.net wine wrapper)
        std::wstring wot_osx = std::wstring(L"Z:\\Users\\") + std::wstring(buf.data()) + std::wstring(L"\\Library\\Application Support\\World of Tanks\\Bottles\\worldoftanks\\drive_c\\Games\\World_of_Tanks\\");
        if (Filesystem::Exists(wot_osx)) {
            WotDetector::AddClient(wot_osx);
        }
    }

    for (auto& drive : drives){
        for (auto& path : pathes){
            try {
                auto drive_path = drive + path;

                if (!std::filesystem::exists(drive_path)) {
                    continue;
                }

                for (auto& p : std::filesystem::directory_iterator(drive_path)) {

                    if (!std::filesystem::is_directory(p)) {
                        continue;
                    }

                    WotDetector::AddClient(p.path());
                }
            }
            catch (std::filesystem::filesystem_error & ex) {
                continue;
            }
            catch (std::system_error & ex) {
                continue;
            }
        }
    }

    WotDetector::isInitialized = true;
}

int WotDetector::AddClient(std::wstring directory, WgcFlavour flavour)
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

bool WotDetector::IsInitialized()
{
    return isInitialized;
}
