// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <filesystem>
#include <string>

#include "module_wgc/wgc_flavour.h"

enum ClientBranch
{
    WoT_Unknown = 0,
    WoT_Release = 1,
    WoT_CommonTest = 2,
    WoT_SuperTest = 3,
    WoT_Sandbox = 4,
};

enum ClientType
{
    WoTType_Unknown = 0,
    WoTType_SD = 1,
    WoTType_HD = 2,
};


class WotClient {
public:
    WotClient();
    WotClient(const std::filesystem::path& wotDirectory, WgcFlavour flavour = WgcFlavour::Unknown);
    ~WotClient() = default;

    bool IsValid();

    std::wstring GetPath();
    void SetPath(const std::filesystem::path& path);

    ClientBranch GetClientBranch();
    std::wstring GetClientExeVersion();
    std::wstring GetClientVersion();
    std::wstring GetClientLocale();
    ClientType GetClientType();
    WgcFlavour GetClientWgcFlavour();

private:
    void updateData();
    bool updateData_apptype();
    bool updateData_gameinfo();
    bool updateData_versionxml();

    void clear();
private:
    bool isValid = false;

    std::filesystem::path path;

    ClientBranch clientBranch = ClientBranch::WoT_Unknown;
    ClientType clientType = ClientType::WoTType_Unknown;
    WgcFlavour _wgcFlavour = WgcFlavour::Unknown;

    std::wstring exeVersion;
    std::wstring clientVersion;

    std::wstring clientLocale;
};
