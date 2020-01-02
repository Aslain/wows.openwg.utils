/* Copyright (c) 2017-2020, Mikhail Paulyshka.
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

#include <algorithm>
#include <filesystem>
#include <iostream>

#include <Windows.h>

#include "wotfinder.h"

#include "common/filesystem.h"
#include "module_wine/wine.h"
#include "module_wgc/wgc.h"
#include "wotlauncher.h"

bool WotDetector::isInitialized = false;
std::vector<WotClient> WotDetector::clients;

void WotDetector::FindClients()
{
    // WGC
    auto wgcPath = WGC::GetWGCInstallPath();
    if (!wgcPath.empty())
    {
        WotDetector::AddClient(WGC::GetClientPreferedPath());

        for (auto& path : WGC::GetClientPaths()) {
            WotDetector::AddClient(path);
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
        wchar_t* buf = new wchar_t[256]{};
        GetEnvironmentVariableW(L"USERNAME", buf, 256);

        if (wcscmp(wine_status.system, L"Linux")==0)
        {
            // /media/<USERNAME>/ mounted partitions
            std::wstring linux_mounts(std::wstring(L"Z:\\media\\") + std::wstring(buf) + std::wstring(L"\\"));
            if (std::filesystem::exists(linux_mounts))
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
            if (std::filesystem::exists(L"Z:\\Volumes\\"))
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
        std::wstring wot_osx = std::wstring(L"Z:\\Users\\") + std::wstring(buf) + std::wstring(L"\\Library\\Application Support\\World of Tanks\\Bottles\\worldoftanks\\drive_c\\Games\\World_of_Tanks\\");
        if (std::filesystem::exists(wot_osx)) {
            WotDetector::AddClient(wot_osx);
        }

        delete[] buf;
    }

    for (auto& drive : drives){
        for (auto& path : pathes){
            try {
                for (auto& p : std::filesystem::directory_iterator(drive + path)) {

                    if (!std::filesystem::is_directory(p)) {
                        continue;
                    }

                    WotDetector::AddClient(p.path());
                }
            }
            catch (std::filesystem::filesystem_error & ex) {
                continue;
            }
        }
    }

    WotDetector::isInitialized = true;
}

int WotDetector::AddClient(std::wstring directory)
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


    WotClient client(directory);
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
