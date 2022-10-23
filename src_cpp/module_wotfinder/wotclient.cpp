// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#include "wotclient.h"

#include "common/filesystem.h"
#include "common/string.h"

#include <filesystem>


#include "pugixml.hpp"

bool WotClient::IsValid()
{
    return isValid;
}

////////CTOR
WotClient::WotClient()
{
}

WotClient::WotClient(const std::filesystem::path& wotDirectory, WgcFlavour flavour)
{
    SetPath(wotDirectory);
    _wgcFlavour = flavour;
}


////GET/SET
std::wstring WotClient::GetPath()
{
    return path;
}

void WotClient::SetPath(const std::filesystem::path& path)
{
    this->path = path;
    updateData();
}

ClientBranch WotClient::GetClientBranch()
{
    return clientBranch;
}

std::wstring WotClient::GetClientExeVersion()
{
    return this->exeVersion;
}

std::wstring WotClient::GetClientVersion()
{
    return clientVersion;
}

std::wstring WotClient::GetClientLocale()
{
    return clientLocale;
}

ClientType WotClient::GetClientType()
{
    return clientType;
}

////////
void WotClient::updateData()
{
    clear();

    bool exe_found = false;
    if (Filesystem::Exists(path / "win64" / L"WorldOfTanks.exe")) {
        exeVersion = Filesystem::GetExeVersion(path / "win64" / L"WorldOfTanks.exe");
        exe_found = true;
    }
    else if (Filesystem::Exists(path / "win32" / L"WorldOfTanks.exe")) {
        exeVersion = Filesystem::GetExeVersion(path / "win32" / L"WorldOfTanks.exe");
        exe_found = true;
    }
    else if (Filesystem::Exists(path / L"WorldOfTanks.exe")) {
        exeVersion = Filesystem::GetExeVersion(path / L"WorldOfTanks.exe");
        exe_found = true;
    }

    if (!exe_found) {
        return;
    }

    if (!updateData_versionxml()){
        return;
    }

    if (!updateData_apptype()){
        return;
    }

    isValid = true;
    updateData_gameinfo();
}

bool WotClient::updateData_apptype()
{
    auto apptypexml = path / L"app_type.xml";
    if (!Filesystem::Exists(apptypexml)) {
        return false;
    }

    pugi::xml_document doc;
    if (!doc.load_file(apptypexml.wstring().c_str())) {
        return false;
    }

    auto apptype = doc.select_single_node(L"/protocol/app_type");
    if (!apptype) {
        return false;
    }

    std::wstring value = apptype.node().first_child().value();
    if (value == L"sd") {
        this->clientType = ClientType::WoTType_SD;
    }
    else if (value == L"hd") {
        this->clientType = ClientType::WoTType_HD;
    }

    return true;
}

bool WotClient::updateData_gameinfo()
{
    auto gameinfoxml = path / L"game_info.xml";
    if (!Filesystem::Exists(gameinfoxml)) {
        return false;
    }

    pugi::xml_document doc;
    if (!doc.load_file(gameinfoxml.wstring().c_str())) {
        return false;
    }

    auto localization = doc.select_single_node(L"/protocol/game/localization");
    if (!localization) {
        return false;
    }

    clientLocale = localization.node().first_child().value();
    return true;
}

bool WotClient::updateData_versionxml()
{
    auto versionxml = path / L"version.xml";
    if (!Filesystem::Exists(versionxml)) {
        return false;
    }


    pugi::xml_document doc;
    if (!doc.load_file(versionxml.wstring().c_str())) {
        return false;
    }

    auto version = doc.select_single_node(L"/version.xml/version");
    if (!version) {
        return false;
    }

    //get client version
    clientVersion = version.node().first_child().value();
    clientVersion = String::Trim(clientVersion);
    clientVersion = String::Replace(clientVersion, L"v.", L"");
    if (clientVersion.find(L'#') != std::wstring::npos) {
        clientVersion = String::Substring(clientVersion, 0, clientVersion.find(L'#'));
    }
    this->clientVersion = String::Trim(clientVersion);

    //get client type
    std::wstring type;
    auto version_tokens = String::Split(clientVersion, L' ', 2);
    if (version_tokens.size() == 2) {
        type = String::Trim(version_tokens[1]);
    }
    this->clientVersion = version_tokens[0];

    if (type.empty())
    {
        this->clientBranch = ClientBranch::WoT_Release;
    }
    else if (type == L"Common Test")
    {
        this->clientBranch = ClientBranch::WoT_CommonTest;
    }
    else if (type == L"ST")
    {
        this->clientBranch = ClientBranch::WoT_SuperTest;
    }
    else if (type == L"SB")
    {
        this->clientBranch = ClientBranch::WoT_Sandbox;
    }
    else
    {
        this->clientBranch = ClientBranch::WoT_Unknown;
    }

    //get locale
    auto localization = doc.select_single_node(L"/version.xml/meta/localization");
    if (!localization) {
        return false;
    }

    auto locale = String::Trim(std::wstring(localization.node().first_child().value()));
    clientLocale = locale.substr(locale.find(L' ') + 1);

    return true;
}

void WotClient::clear()
{
    isValid = false;
    clientBranch = ClientBranch::WoT_Unknown;
    exeVersion.clear();
    clientVersion.clear();
}

WgcFlavour WotClient::GetClientWgcFlavour() {
    return _wgcFlavour;
}
