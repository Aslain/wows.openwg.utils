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

WotClient::WotClient(const std::filesystem::path& wotDirectory)
{
    SetPath(wotDirectory);
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

    if (!std::filesystem::exists(path / L"WorldOfTanks.exe")){
        return;
    }

    exeVersion = Filesystem::GetExeVersion(path /  L"WorldOfTanks.exe");
    if (exeVersion == L"0.0.0.0" && std::filesystem::exists(path / "win32" / L"WorldOfTanks.exe")) {
        exeVersion = Filesystem::GetExeVersion(path / "win32" / L"WorldOfTanks.exe");
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
    if (!std::filesystem::exists(apptypexml)) {
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
    if (!std::filesystem::exists(gameinfoxml)) {
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
    if (!std::filesystem::exists(versionxml)) {
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


    std::wstring clientver = version.node().first_child().value();
    clientver.replace(clientver.find(L" v."), std::wstring(L" v.").length(), L"");
    clientVersion = clientver.substr(0, clientver.find(L' '));
    std::wstring type = clientver.substr(clientver.find(L' ') + 1);
    type = type.substr(0, type.find(L'#'));
    type = String::Trim(type);

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
