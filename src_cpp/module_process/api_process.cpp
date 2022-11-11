// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "module_process/api_process.h"
#include "module_process/process_module.h"

using namespace OpenWG::Utils;

int32_t PROCESS_GetRunningInDirectoryW(const wchar_t * directory_path, wchar_t * output_list, int32_t output_list_size)
{
    if(!directory_path || !output_list ){
        return false;
    }
    if (output_list_size == 0) {
        return false;
    }
    output_list[0] = L'\0';

    auto procs = Process::GetRunningProcessesInDirectory(directory_path);
    if (procs.empty()) {
        return false;
    }

    std::wstring output = L"";
    for (auto&proc : procs) {
        output += proc.wstring() + L";";
    }
    output.pop_back();

    wcscpy_s(output_list, output_list_size, output.c_str());

    return true;
}

int32_t PROCESS_TerminateProcess(const wchar_t * processName)
{
    return Process::TerminateProcess(processName);
}
