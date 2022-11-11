// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace OpenWG::Utils::Common {
    namespace Filesystem {

        std::wstring GetExeVersion(const std::wstring &filepath);

        std::wstring GetFileContent(const std::wstring &filepath);

        std::filesystem::path GetProgramDataPath();

        std::vector<std::wstring> GetLogicalDrives();

        bool Exists(const std::filesystem::path &path);
    }
}
