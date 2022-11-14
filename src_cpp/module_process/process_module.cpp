// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include <algorithm>

#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>

#include "common/filesystem.h"
#include "common/string.h"
#include "module_process/process_module.h"


namespace OpenWG::Utils::Process {

    std::wstring NormalizeNTPath(const wchar_t* str)
    {
        if(!str){
            return {};
        }

        std::wstring result{str};

        for (wchar_t drive_letter = L'A'; drive_letter <= L'Z'; drive_letter++)
        {
            wchar_t driver_letter_str[3]{};
            driver_letter_str[0] = drive_letter;
            driver_letter_str[1] = L':';

            wchar_t nt_drive_path[256]{};

            auto size = QueryDosDeviceW(driver_letter_str, nt_drive_path, std::size(nt_drive_path));
            if(size){
                if(result.starts_with(nt_drive_path)){
                    result = result.replace(0, size-2, driver_letter_str);
                    break;
                }
            }
        }

        return result;
    }

    std::map<std::filesystem::path, uint32_t> GetProcessList() {
        std::map<std::filesystem::path, uint32_t> result{};

        HANDLE handle_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (handle_snapshot != INVALID_HANDLE_VALUE) {

            PROCESSENTRY32W process_entry{};
            process_entry.dwSize = sizeof(process_entry);

            if (Process32FirstW(handle_snapshot, &process_entry)) {
                do {
                    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, process_entry.th32ProcessID);
                    if (!hProcess) {
                        continue;
                    }

                    wchar_t pName[path_maxsize]{};
                    if (GetProcessImageFileNameW(hProcess, pName, sizeof(pName))) {
                        auto path = std::filesystem::path(NormalizeNTPath(pName)).lexically_normal();
                        result.emplace(path, process_entry.th32ProcessID);
                    }

                    CloseHandle(hProcess);
                } while (Process32NextW(handle_snapshot, &process_entry));
            }

            CloseHandle(handle_snapshot);
        }

        return result;
    }

    std::vector<std::filesystem::path> GetRunningProcessesInDirectory(const std::filesystem::path &directoryName) {
        std::vector<std::filesystem::path> result;

        //normalize directory
        auto dir_norm = directoryName.lexically_normal();

        for (const auto &process: GetProcessList()) {
            if (Common::Filesystem::IsSubpath(process.first, dir_norm)) {
                result.emplace_back(process.first);
            }
        }

        return result;
    }

    BOOL CALLBACK TerminateProcessCallback(
            _In_ HWND hwnd,
            _In_ LPARAM lParam
    ) {
        DWORD dwID = 0;
        PDWORD_PTR lResult = nullptr;

        GetWindowThreadProcessId(hwnd, &dwID);

        if (dwID == lParam) {
            return SendMessageTimeoutW(hwnd, WM_CLOSE, 0, 0, SMTO_BLOCK | SMTO_ABORTIFHUNG, 5000, lResult) != 0;
        } else {
            return true;
        }
    }

    bool TerminateProcess(uint32_t processID) {
        bool result{false};

        HANDLE hProcess = OpenProcess(
                PROCESS_TERMINATE | PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | SYNCHRONIZE, FALSE,
                processID);
        if (hProcess) {
            if (EnumWindows(TerminateProcessCallback, processID)) {
                switch (WaitForSingleObject(hProcess, 5000)) {
                    case WAIT_OBJECT_0:
                        CloseHandle(hProcess);
                        break;
                    default:
                        break;
                }
            }

            ::TerminateProcess(hProcess, 9);
            result = true;
        }

        return result;
    }

    bool TerminateProcess(const std::wstring &processName) {
        bool result{false};

        for (auto &process: GetProcessList()) {
            if (Common::String::ToLower(process.first) == Common::String::ToLower(processName)) {
                result = TerminateProcess(process.second);
            }
        }

        return result;
    }
}
