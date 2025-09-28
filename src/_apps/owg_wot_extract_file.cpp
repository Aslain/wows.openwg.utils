// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2025 OpenWG.Utils Contributors

//
// Includes
//

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <vector>

#include "wot/api_wot.h"

namespace {

std::wstring read_line(const std::wstring& prompt, bool allow_empty = false) {
    std::wstring line;
    while (true) {
        std::wcout << prompt;
        if (!std::getline(std::wcin, line)) {
            std::wcin.clear();
            if (allow_empty) {
                return {};
            }
            continue;
        }
        // trim trailing carriage return if present (Windows terminals)
        if (!line.empty() && line.back() == L'\r') {
            line.pop_back();
        }
        if (line.empty() && !allow_empty) {
            std::wcout << L"Input cannot be empty. Please try again." << std::endl;
            continue;
        }

        break;
    }
    return line;
}

void print_clients() {
    const int32_t count = WOT_GetClientsCount();
    std::wcout << L"Detected clients: " << count << std::endl;

    wchar_t buffer[1024]{};

    for (int32_t idx = 0; idx < count; ++idx) {
        WOT_GetClientPathW(buffer, std::size(buffer), idx);
        const std::wstring client_path(buffer);

        WOT_GetClientVersionW(buffer, std::size(buffer), idx);
        const std::wstring client_version(buffer);

        const auto vendor = WOT_GetClientVendor(idx);
        std::wstring vendor_str = L"Unknown";
        switch (vendor) {
            case ClientVendor::WoT_Vendor_WG:
                vendor_str = L"WG";
                break;
            case ClientVendor::WoT_Vendor_Lesta:
                vendor_str = L"Lesta";
                break;
            default:
                break;
        }

        const auto branch = WOT_GetClientBranch(idx);
        std::wstring branch_str = L"Unknown";
        switch (branch) {
            case ClientBranch::WoT_Branch_Release:
                branch_str = L"Release";
                break;
            case ClientBranch::WoT_Branch_CommonTest:
                branch_str = L"Common Test";
                break;
            case ClientBranch::WoT_Branch_SuperTest:
                branch_str = L"Super Test";
                break;
            case ClientBranch::WoT_Branch_Sandbox:
                branch_str = L"Sandbox";
                break;
            case ClientBranch::WoT_Branch_ClosedTest:
                branch_str = L"Closed Test";
                break;
            default:
                break;
        }

        std::wcout << L"[" << idx << L"] " << client_path << std::endl;
        std::wcout << L"    Version: " << client_version << std::endl;
        std::wcout << L"    Vendor : " << vendor_str << std::endl;
        std::wcout << L"    Branch : " << branch_str << std::endl;
    }
}

std::optional<std::filesystem::path> parse_destination_path(const std::wstring& input) {
    if (input.empty()) {
        return std::nullopt;
    }

    std::filesystem::path path = std::filesystem::path(input).lexically_normal();
    return path;
}

int32_t read_client_index(int32_t max_index) {
    while (true) {
        const std::wstring input = read_line(L"Enter client index: ");

        try {
            const long value = std::stol(input);
            if (value < 0 || value >= max_index) {
                std::wcout << L"Index is out of range. Valid range [0, " << (max_index - 1) << L"]." << std::endl;
                continue;
            }
            return static_cast<int32_t>(value);
        } catch (const std::exception&) {
            std::wcout << L"Invalid number. Please enter a valid integer value." << std::endl;
        }
    }
}

} // namespace

int wmain() {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    std::wcout << L"OpenWG.Utils: WoT package file extractor" << std::endl;

    // Ensure launchers are rescanned to get up-to-date client list.
    WOT_LauncherRescan();

    const int32_t client_count = WOT_GetClientsCount();
    if (client_count <= 0) {
        std::wcout << L"No clients detected. Press Enter to exit." << std::endl;
        std::wcin.get();
        return 1;
    }

    print_clients();
    const int32_t client_index = read_client_index(client_count);

    std::wcout << std::endl;
    std::wcout << L"Provide the file path inside packages (use forward slashes)." << std::endl;
    std::wcout << L"Example entry path: scripts/item_defs/vehicles/common.xml" << std::endl << std::endl;

    const std::wstring entry_path = read_line(L"Enter package entry path: ");
    const std::wstring destination_input = read_line(L"Enter output file path (leave empty to use current directory): ", true);

    std::optional<std::filesystem::path> destination_path = parse_destination_path(destination_input);
    if (!destination_path) {
        std::filesystem::path default_output = std::filesystem::current_path() / std::filesystem::path(entry_path).filename();
        destination_path = default_output.lexically_normal();
    }

    const int32_t package_count = WOT_ClientGetPackagesCount(client_index);
    if (package_count <= 0) {
        std::wcout << L"No packages detected for the selected client. Extraction cannot continue." << std::endl;
        std::wcout << L"Press Enter to exit." << std::endl;
        std::wcin.get();
        return 2;
    }

    std::wcout << L"Searching " << package_count << L" package(s) for entry '" << entry_path << L"'..." << std::endl;

    bool extracted = false;
    wchar_t package_buffer[1024]{};

    for (int32_t pkg_idx = 0; pkg_idx < package_count; ++pkg_idx) {
        int32_t pkg_result = WOT_ClientGetPackagePathW(client_index, pkg_idx, package_buffer, std::size(package_buffer));
        if (pkg_result <= 0) {
            continue;
        }

        std::wcout << L" - Checking: " << package_buffer << std::endl;
        const int32_t result = WOT_ClientExtractPackageFileToFileW(
            client_index,
            package_buffer,
            entry_path.c_str(),
            destination_path->wstring().c_str());

        if (result == 1) {
            std::wcout << L"Entry extracted from package '" << package_buffer << L"' to '" << destination_path->wstring() << L"'." << std::endl;
            extracted = true;
            break;
        }
    }

    if (!extracted) {
        std::wcout << L"Unable to locate entry '" << entry_path << L"' in available packages." << std::endl;
    }

    std::wcout << L"Press Enter to exit." << std::endl;
    std::wcin.get();
    return extracted ? 0 : 3;
}