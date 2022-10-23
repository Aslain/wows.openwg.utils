// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <filesystem>
#include <string>
#include <vector>

class Filesystem
{
public:
    static std::wstring GetExeVersion(const std::wstring& filepath);
    static std::wstring GetFileContent(const std::wstring& filepath);
    static std::filesystem::path GetProgramDataPath();
    static std::vector<std::wstring> GetLogicalDrives();
    static bool Exists(const std::filesystem::path& path);
};
