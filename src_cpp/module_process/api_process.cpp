// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "api_process.h"

#include "process_module.h"

bool PROCESS_GetRunningInDirectoryW(wchar_t * directory_path, wchar_t * output_list, int32_t output_list_size)
{
    if (output_list_size == 0) {
        return false;
    }

    if (output_list == nullptr) {
        return false;
    }

    output_list[0] = L'\0';

    std::vector<std::wstring> procs = Process::GetRunningProcessesInDirectory(directory_path);

    if (procs.size() == 0)
        return false;

    std::wstring output = L"";
    for (auto&proc : procs) {
        output += proc + L";";
    }
    output.pop_back();

    wcscpy_s(output_list, output_list_size, output.c_str());

    return true;
}

bool PROCESS_TerminateProcess(wchar_t * processName)
{
    return Process::TerminateProcess(processName);
}
