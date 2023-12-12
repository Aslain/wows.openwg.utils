// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "fs.h"

#include <array>
#include <codecvt>
#include <fstream>
#include <locale>


#include <Windows.h>
#include <ShlObj.h>
#include "wine/wine.h"

namespace OpenWG::Utils {
    namespace Filesystem {

        std::wstring GetExeVersion(const std::wstring &filepath) {
            std::wstring result;

            unsigned long verHandle = 0;
            unsigned int size = 0;
            unsigned char *lpBuffer = nullptr;
            unsigned long verSize = GetFileVersionInfoSizeW(filepath.c_str(), &verHandle);

            if (verSize == 0) {
                return result;
            }

            wchar_t *verData = new wchar_t[verSize];

            if (GetFileVersionInfoW(filepath.c_str(), verHandle, verSize, verData)) {
                if (VerQueryValueW(verData, L"\\", (void **) &lpBuffer, &size)) {
                    if (size) {
                        VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *) lpBuffer;
                        if (verInfo->dwSignature == 0xfeef04bd) {
                            result = std::to_wstring((verInfo->dwFileVersionMS >> 16) & 0xffff) +
                                     +L"." + std::to_wstring((verInfo->dwFileVersionMS >> 0) & 0xffff) +
                                     +L"." + std::to_wstring((verInfo->dwFileVersionLS >> 16) & 0xffff) +
                                     +L"." + std::to_wstring((verInfo->dwFileVersionLS >> 0) & 0xffff);
                        }
                    }
                }
            }

            delete[] verData;
            return result;
        }

        std::wstring GetFileContent(const std::wstring &filepath) {
            std::wstring content;

            std::wifstream in(std::filesystem::path(filepath), std::wifstream::in);
            if (!in.is_open()) {
                return std::wstring();
            }
            in.imbue(std::locale(in.getloc(), new std::codecvt_utf8_utf16<wchar_t, 0x10FFFF, std::consume_header>()));

            content.assign(std::istreambuf_iterator<wchar_t>(in), std::istreambuf_iterator<wchar_t>());
            in.close();

            return content;
        }

        std::filesystem::path GetProgramDataPath() {
            wchar_t szProgramDataPath[MAX_PATH]{0};
            if (!SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_COMMON_APPDATA, NULL, 0, szProgramDataPath))) {
                return std::filesystem::path();
            }
            return std::filesystem::path(szProgramDataPath);
        }

        std::vector<std::wstring> GetLogicalDrives() {
            std::vector<std::wstring> drives;

            const unsigned int buffer_length = 1024;
            wchar_t *buffer = new wchar_t[buffer_length];

            DWORD dwResult = GetLogicalDriveStringsW(buffer_length, buffer);
            if (dwResult > 0 && dwResult <= buffer_length) {
                wchar_t *singleDrive = buffer;
                while (*singleDrive) {
                    unsigned int drive_type = GetDriveTypeW(singleDrive);
                    if ((drive_type != DRIVE_CDROM) && (drive_type != DRIVE_UNKNOWN) &&
                        (drive_type != DRIVE_NO_ROOT_DIR)) {
                        drives.push_back(singleDrive);
                    }
                    singleDrive += wcslen(singleDrive) + 1;
                }
            }

            // Non-windows additions
            Wine::WineStatus wine_status = Wine::GetStatus();
            if (wine_status.running_on) {
                std::array<wchar_t, 256> buf{};
                GetEnvironmentVariableW(L"USERNAME", buf.data(), 256);

                if (wcsicmp(wine_status.system, L"Linux") == 0) {
                    // /media/<USERNAME>/ mounted partitions
                    std::wstring linux_mounts(
                            std::wstring(L"Z:\\media\\") + std::wstring(buf.data()) + std::wstring(L"\\"));
                    if (Filesystem::Exists(linux_mounts)) {
                        for (auto &p: std::filesystem::directory_iterator(linux_mounts)) {
                            if (!std::filesystem::is_directory(p))
                                continue;

                            drives.push_back(p.path().wstring() + L"\\");
                        }
                    }
                }

                if (wcsicmp(wine_status.system, L"Darwin") == 0) {
                    // /Volumes/ mounted partitions
                    if (Filesystem::Exists(L"Z:\\Volumes\\")) {
                        for (auto &p: std::filesystem::directory_iterator(L"Z:\\Volumes\\")) {
                            if (!std::filesystem::is_directory(p))
                                continue;

                            drives.push_back(p.path().wstring() + L"\\");
                        }
                    }
                }

            }

            return drives;
        }

        bool Exists(const std::filesystem::path &path) {
            bool result = false;

            try {
                result = std::filesystem::exists(path);
            }
            catch (const std::filesystem::filesystem_error &) {}

            return result;
        }

        bool IsSubpath(const std::filesystem::path &path, const std::filesystem::path &base) {
            auto rel = std::filesystem::relative(path, base);
            return !rel.empty() && rel.native()[0] != '.';
        }

        bool IsEqual(const std::filesystem::path &path_1, const std::filesystem::path &path_2) {
            if (!std::filesystem::exists(path_1) || !std::filesystem::exists(path_2)) {
                return false;
            }
            if (!std::filesystem::is_regular_file(path_1) || !std::filesystem::is_regular_file(path_2)) {
                return false;
            }
            if (std::filesystem::file_size(path_1) != std::filesystem::file_size(path_2)) {
                return false;
            }

            std::ifstream stream_1(path_1, std::ifstream::binary);
            std::ifstream stream_2(path_2, std::ifstream::binary);

            return std::equal(std::istreambuf_iterator<char>(stream_1.rdbuf()),
                              std::istreambuf_iterator<char>(),
                              std::istreambuf_iterator<char>(stream_2.rdbuf()));
        }


    }
}
