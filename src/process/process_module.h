// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <cstdint>
#include <filesystem>
#include <limits>
#include <map>
#include <vector>
#include <string>

namespace OpenWG::Utils::Process {

    constexpr auto path_maxsize = std::numeric_limits<int16_t>::max();

    std::vector<std::pair<std::filesystem::path, uint32_t>> GetProcessList();

    std::vector<std::filesystem::path> GetRunningProcessesInDirectory(const std::filesystem::path& directoryPath);

    bool TerminateProcess(uint32_t processID);

    bool TerminateProcess(const std::wstring& processName);
};