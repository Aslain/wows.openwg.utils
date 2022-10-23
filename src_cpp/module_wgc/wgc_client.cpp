// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "pugixml.hpp"

#include "common/filesystem.h"

#include "wgc_client.h"

WgcClient::WgcClient(const std::filesystem::path &path, WgcFlavour flavour) {
    _path = path;
    _flavour = flavour;
}

std::vector<std::filesystem::path> WgcClient::GetClientPaths()
{
    std::vector<std::filesystem::path> wotPaths;

    //Program data
    try{
        for (auto& p : std::filesystem::directory_iterator(_path / "apps")){
            if(p.path().filename().string().find("wot.") != 0){
                continue;
            }

            for (auto& pp : std::filesystem::directory_iterator(p)) {
                auto path = std::filesystem::path(Filesystem::GetFileContent(pp.path().wstring()));

                if (Filesystem::Exists(path / L"WorldOfTanks.exe")) {
                    wotPaths.push_back(path);
                }
            }
        }
    }
    catch (const std::exception&) {}

    //WGC_dir/preferences.xml
    try {
        auto preferencesPath = _path / L"preferences.xml";
        if (Filesystem::Exists(preferencesPath)) {
            pugi::xml_document doc;
            if (doc.load_file(preferencesPath.wstring().c_str())) {

                //selected wot game
                auto wot = doc.select_single_node(L"/protocol/application/games_manager/selectedGames/WOT");
                if (wot) {
                    wotPaths.push_back(wot.node().first_child().value());
                }

                //process
                auto games = doc.select_single_node(L"/protocol/application/games_manager/games");
                if (games) {
                    for (auto& game : games.node()) {
                        auto wd = game.select_single_node(L".//working_dir");
                        if (!wd) {
                            continue;
                        }

                        wotPaths.push_back(wd.node().first_child().value());
                    }

                }
            }
        }
    }
    catch (const std::exception&) {}

    return wotPaths;
}


std::filesystem::path WgcClient::GetClientPreferredPath()
{
    auto preferencesPath = _path / L"preferences.xml";
    if (!Filesystem::Exists(preferencesPath)) {
        return std::filesystem::path();
    }

    pugi::xml_document doc;
    if (!doc.load_file(preferencesPath.wstring().c_str())) {
        return std::filesystem::path();
    }

    auto wot = doc.select_single_node(L"/protocol/application/games_manager/selectedGames/WOT");
    if (!wot) {
        return std::filesystem::path();
    }

    return std::filesystem::path(wot.node().first_child().value());
}

WgcFlavour WgcClient::GetFlavour() {
    return _flavour;
}
