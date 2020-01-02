/* Copyright (c) 2017-2020, Mikhail Paulyshka.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "api_process.h"

#include "process.h"

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
