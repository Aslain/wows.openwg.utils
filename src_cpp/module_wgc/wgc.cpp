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

#include "wgc.h"
#include "common/filesystem.h"

#include <filesystem>

#include "pugixml.hpp"


std::filesystem::path WGC::GetWGCInstallPath()
{
    auto programDataPath = Filesystem::GetProgramDataPath();

    auto wgcPathFile = programDataPath / L"Wargaming.net" / L"GameCenter" / "data" / "wgc_path.dat";
    if (Filesystem::Exists(wgcPathFile)){
        auto path = std::filesystem::path(Filesystem::GetFileContent(wgcPathFile));
        if (Filesystem::Exists(path / "wgc.exe")){
            return path;
        }
    }
    else if (Filesystem::Exists(programDataPath / "Wargaming.net" / "GameCenter" / "wgc.exe")){
        return programDataPath / "Wargaming.net" / "GameCenter";
    }

    return  std::filesystem::path();
}


std::vector<std::filesystem::path> WGC::GetClientPaths()
{
    std::wstring programDataPath = Filesystem::GetProgramDataPath();

    std::vector<std::filesystem::path> wotPaths;

    try{
        for (auto& p : std::filesystem::directory_iterator(programDataPath + L"\\Wargaming.net\\GameCenter\\apps\\wot\\")){
            auto path = std::filesystem::path(Filesystem::GetFileContent(p.path().wstring()));

            if (Filesystem::Exists(path / L"WorldOfTanks.exe")){
                wotPaths.push_back(path);
            }
        }
    }
    catch (const std::exception&) {}

    return wotPaths;
}


std::filesystem::path WGC::GetClientPreferedPath()
{
    auto preferencesPath = GetWGCInstallPath() / L"preferences.xml";
    if (!Filesystem::Exists(preferencesPath)) {
        return std::filesystem::path();
    }

    pugi::xml_document doc;
    if (!doc.load_file(preferencesPath.wstring().c_str())) {
        return false;
    }

    auto wot = doc.select_single_node(L"/protocol/application/games_manager/selectedGames/WOT");
    if (!wot) {
        return std::filesystem::path();
    }

    return std::filesystem::path(wot.node().first_child().value());
}
