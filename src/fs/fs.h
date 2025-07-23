// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace OpenWG::Utils {
    namespace Filesystem {

        [[nodiscard]] std::wstring GetExeVersion(const std::wstring &filepath);

        [[nodiscard]] std::wstring GetFileContent(const std::wstring &filepath);

        [[nodiscard]] std::filesystem::path GetProgramDataPath();

        [[nodiscard]] std::vector<std::wstring> GetLogicalDrives();

        [[nodiscard]] bool Exists(const std::filesystem::path &path);

        [[nodiscard]] bool IsEqual(const std::filesystem::path& path_1, const std::filesystem::path& path_2);

        [[nodiscard]] bool IsSubpath(const std::filesystem::path &path, const std::filesystem::path &base);

        [[nodiscard]] size_t Size(const std::filesystem::path &path);
    }
}
