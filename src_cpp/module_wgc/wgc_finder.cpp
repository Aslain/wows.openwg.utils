// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "common/filesystem.h"

#include "wgc_finder.h"

std::vector<WGCInfo> WgcFinder::_wgcs = {
    {
        L"Wargaming.net//GameCenter", WgcFlavour::WG, L"wgc_path.dat", L"wgc.exe"
    },
    {
        L"360 Wargaming//GameCenter", WgcFlavour::China360, L"wgc_path.dat", L"wgc.exe"
    },
    {
        L"Wargaming.net//GameCenter for Steam", WgcFlavour::Steam, L"wgc_path.dat", L"wgc.exe"
    },
    {
        L"Lesta//GameCenter", WgcFlavour::Lesta, L"lgc_path.dat", L"lgc.exe"
    }
};

std::vector<WgcClient> WgcFinder::GetWgcClients() {
    std::vector<WgcClient> result;

    auto program_data_path = Filesystem::GetProgramDataPath();
    for(auto& wgc : _wgcs){
        auto wgc_path_file = program_data_path / wgc.prefix / "data" / wgc.path_filename;

        if (Filesystem::Exists(wgc_path_file)){
            auto wgc_path_content = std::filesystem::path(Filesystem::GetFileContent(wgc_path_file));
            if (Filesystem::Exists(wgc_path_content / wgc.exe_filename)){
                result.push_back(WgcClient(wgc_path_content, wgc.flavour));
            }
        }
    }

    return result;
}
