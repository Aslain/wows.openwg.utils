// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "filesystem.h"

#include <codecvt>
#include <fstream>
#include <locale>

#include <ShlObj.h>
#include <Windows.h>

std::wstring Filesystem::GetExeVersion(const std::wstring & filepath)
{
    std::wstring result;

    unsigned long  verHandle = 0;
    unsigned int   size = 0;
    unsigned char* lpBuffer = nullptr;
    unsigned long  verSize = GetFileVersionInfoSizeW(filepath.c_str(), &verHandle);

    if (verSize == 0)
    {
        return result;
    }

    wchar_t* verData = new wchar_t[verSize];

    if (GetFileVersionInfoW(filepath.c_str(), verHandle, verSize, verData))
    {
        if (VerQueryValueW(verData, L"\\", (void**)&lpBuffer, &size))
        {
            if (size)
            {
                VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
                if (verInfo->dwSignature == 0xfeef04bd)
                {
                    result = std::to_wstring((verInfo->dwFileVersionMS >> 16) & 0xffff) +
                        + L"." + std::to_wstring((verInfo->dwFileVersionMS >> 0) & 0xffff) +
                        + L"." + std::to_wstring((verInfo->dwFileVersionLS >> 16) & 0xffff) +
                        + L"." + std::to_wstring((verInfo->dwFileVersionLS >> 0) & 0xffff);
                }
            }
        }
    }

    delete[] verData;
    return result;
}

std::wstring Filesystem::GetFileContent(const std::wstring& filepath)
{
    std::wstring content;

    std::wifstream in(filepath, std::wifstream::in);
    if (!in.is_open())
    {
        return std::wstring();
    }
    in.imbue(std::locale(in.getloc(), new std::codecvt_utf8_utf16<wchar_t, 0x10FFFF, std::consume_header>()));

    content.assign(std::istreambuf_iterator<wchar_t>(in), std::istreambuf_iterator<wchar_t>());
    in.close();

    return content;
}

std::filesystem::path Filesystem::GetProgramDataPath()
{
    wchar_t szProgramDataPath[MAX_PATH]{ 0 };
    if (!SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_COMMON_APPDATA, NULL, 0, szProgramDataPath))){
        return std::filesystem::path();
    }
    return std::filesystem::path(szProgramDataPath);
}

std::vector<std::wstring> Filesystem::GetLogicalDrives()
{
    std::vector<std::wstring> drives;

    const unsigned int buffer_length = 1024;
    wchar_t* buffer = new wchar_t[buffer_length];

    DWORD dwResult = GetLogicalDriveStringsW(buffer_length, buffer);
    if (dwResult > 0 && dwResult <= buffer_length)
    {
        wchar_t* singleDrive = buffer;
        while (*singleDrive)
        {
            unsigned int drive_type = GetDriveTypeW(singleDrive);
            if ((drive_type != DRIVE_CDROM) && (drive_type != DRIVE_UNKNOWN) && (drive_type != DRIVE_NO_ROOT_DIR))
            {
                drives.push_back(singleDrive);
            }
            singleDrive += wcslen(singleDrive) + 1;
        }
    }

    return drives;
}

bool Filesystem::Exists(const std::filesystem::path& path)
{
    bool result = false;

    try {
        result = std::filesystem::exists(path);
    }
    catch (const std::filesystem::filesystem_error&){}

    return result;
}
