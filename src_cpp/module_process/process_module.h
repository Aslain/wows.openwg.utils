// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <filesystem>
#include <limits>
#include <vector>
#include <string>

namespace OpenWG::Utils::Process {

    constexpr auto path_maxsize = std::numeric_limits<int16_t>::max();

    std::map<std::filesystem::path, DWORD> GetProcessList();

    std::vector<std::filesystem::path> GetRunningProcessesInDirectory(const std::filesystem::path& directoryPath);

    bool TerminateProcess(DWORD processID);

    bool TerminateProcess(const std::wstring& processName);
};