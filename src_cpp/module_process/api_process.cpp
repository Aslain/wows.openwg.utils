// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "module_process/api_process.h"
#include "module_process/process_module.h"

using namespace OpenWG::Utils;

int32_t PROCESS_GetRunningInDirectoryW(const wchar_t* directory_path, wchar_t* output_list, int32_t output_list_size)
{
    int32_t result = -1;

    if (directory_path && output_list && output_list_size) {
        output_list[0] = L'\0';
        auto procs = Process::GetRunningProcessesInDirectory(directory_path);
        for (const auto& proc : procs) {
            wcscat_s(output_list, output_list_size, proc.c_str());
            wcscat_s(output_list, output_list_size, L";");
        }
        result = procs.size();
    }

    return result;
}

int32_t PROCESS_TerminateProcess(const wchar_t * processName)
{
    return Process::TerminateProcess(processName);
}
