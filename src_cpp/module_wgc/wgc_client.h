// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <filesystem>
#include <vector>

#include "wgc_flavour.h"

class WgcClient {
public:
    WgcClient(const std::filesystem::path& path, WgcFlavour flavour);

    std::vector<std::filesystem::path> GetClientPaths();

    std::filesystem::path GetClientPreferredPath();

    WgcFlavour GetFlavour();

private:
    WgcFlavour _flavour = WgcFlavour::Unknown;
    std::filesystem::path _path;
};