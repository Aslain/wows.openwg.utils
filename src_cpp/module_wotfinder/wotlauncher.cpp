// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "wotlauncher.h"

#include "common/filesystem.h"
#include "common/registry.h"
#include "common/vector.h"

#include <filesystem>

std::vector<std::filesystem::path> WotLauncher::GetWotPaths() {
    std::vector<std::filesystem::path> paths;

    std::vector<std::wstring> keys = {
        L"SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812ru}_is1",
        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812ru}_is1",
        L"SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812eu}_is1",
        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812eu}_is1",
        L"SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812na}_is1",
        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812na}_is1",
        L"SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812asia}_is1",
        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812asia}_is1",
        L"SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812kr}_is1",
        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812kr}_is1",
        L"SOFTWARE\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812ct}_is1",
        L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\{1EAC1D02-C6AC-4FA6-9A44-96258C37C812ct}_is1" };

    for (auto& p : keys){
        std::wstring path = Registry::GetStringValue(p.c_str(), L"InstallLocation");

        if (!path.empty()) {
            auto p = std::filesystem::path(path);
            if (Filesystem::Exists(p / L"WorldOfTanks.exe")) {
                paths.push_back(p);
            }
        }
    }

    Vector::RemoveDuplicates(paths);
    return paths;
}
