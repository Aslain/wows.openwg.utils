// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace OpenWG::Utils {
    namespace Filesystem {

        std::wstring GetExeVersion(const std::wstring &filepath);

        std::wstring GetFileContent(const std::wstring &filepath);

        std::filesystem::path GetProgramDataPath();

        std::vector<std::wstring> GetLogicalDrives();

        bool Exists(const std::filesystem::path &path);

        [[nodiscard]] bool IsEqual(const std::filesystem::path& path_1, const std::filesystem::path& path_2);

        bool IsSubpath(const std::filesystem::path &path, const std::filesystem::path &base);
    }
}
