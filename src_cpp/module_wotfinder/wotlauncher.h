// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <filesystem>
#include <vector>

class WotLauncher {
public:
    static std::vector<std::filesystem::path> GetWotPaths();
};
