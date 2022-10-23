// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <string>
#include <vector>

class Process
{
public:
    static std::vector<std::wstring> GetRunningProcessesInDirectory(wchar_t* directoryPath);

    static bool TerminateProcess(wchar_t* processName);
};