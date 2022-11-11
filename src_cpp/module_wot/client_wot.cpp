#include <pugixml.hpp>

#include "common/filesystem.h"
#include "common/string.h"
#include "module_wot/client_wot.h"

namespace OpenWG::Utils::WoT {

    ClientWoT::ClientWoT(std::filesystem::path path, LauncherFlavour launcherFlavour) : m_path(std::move(path)),
                                                                                        m_launcherFlavour(
                                                                                                launcherFlavour) {

    }


    bool ClientWoT::IsValid() {
        return Common::Filesystem::Exists(m_path / "app_type.xml") &&
               Common::Filesystem::Exists(m_path / "version.xml") &&
               Common::Filesystem::Exists(m_path / "game_info.xml") &&
               Common::Filesystem::Exists(m_path / "WorldOfTanks.exe");
    }

    ClientBranch ClientWoT::GetBranch() {
        auto versionRaw = getVersionClientRaw();
        if (!versionRaw.has_value()) {
            return WoT_Branch_Unknown;
        }

        //get client type
        std::wstring type;
        auto version_tokens = Common::String::Split(versionRaw.value(), L' ', 2);
        if (version_tokens.size() == 2) {
            type = Common::String::Trim(version_tokens[1]);
        }

        if (type.empty()) {
            return WoT_Branch_Release;
        } else if (type == L"Common Test") {
            return WoT_Branch_CommonTest;
        } else if (type == L"ST") {
            return WoT_Branch_SuperTest;
        } else if (type == L"SB") {
            return WoT_Branch_Sandbox;
        }

        return WoT_Branch_Unknown;
    }

    LauncherFlavour ClientWoT::GetLauncherFlavour() {
        return m_launcherFlavour;
    }

    std::filesystem::path ClientWoT::GetPath() {
        return m_path;
    }

    std::optional<std::wstring> ClientWoT::GetLocale() {
        auto gameinfoxml = m_path / L"game_info.xml";
        if (!Common::Filesystem::Exists(gameinfoxml)) {
            return std::nullopt;
        }

        pugi::xml_document doc;
        if (!doc.load_file(gameinfoxml.wstring().c_str())) {
            return std::nullopt;
        }

        auto localization = doc.select_node(L"/protocol/game/localization");
        if (!localization) {
            return std::nullopt;
        }

        return {localization.node().first_child().value()};
    }


    std::optional<std::wstring> ClientWoT::GetRealm() {
        auto versionxml = m_path / L"version.xml";
        if (!Common::Filesystem::Exists(versionxml)) {
            return std::nullopt;
        }

        pugi::xml_document doc;
        if (!doc.load_file(versionxml.wstring().c_str())) {
            return std::nullopt;
        }

        auto realm = doc.select_node(L"/version.xml/meta/realm");
        if (!realm) {
            return std::nullopt;
        }

        return {Common::String::Trim(realm.node().first_child().value())};
    }

    ClientType ClientWoT::GetType() {
        auto apptypexml = m_path / L"app_type.xml";
        if (!Common::Filesystem::Exists(apptypexml)) {
            return WoT_Type_Unknown;
        }

        pugi::xml_document doc;
        if (!doc.load_file(apptypexml.wstring().c_str())) {
            return WoT_Type_Unknown;
        }

        auto apptype = doc.select_node(L"/protocol/app_type");
        if (apptype) {
            std::wstring value = apptype.node().first_child().value();
            if (value == L"sd") {
                return WoT_Type_SD;
            } else if (value == L"hd") {
                return WoT_Type_HD;
            }
        }

        return WoT_Type_Unknown;
    }

    std::optional<std::wstring> ClientWoT::GetVersionClient() {
        auto rawversion = getVersionClientRaw();
        if (!rawversion.has_value()) {
            return std::nullopt;
        }

        auto version_tokens = Common::String::Split(rawversion.value(), L' ', 2);
        return version_tokens[0];
    }

    std::optional<std::wstring> ClientWoT::GetVersionExe() {
        auto path = m_path / "win64" / L"WorldOfTanks.exe";
        if (Common::Filesystem::Exists(path)) {
            return {Common::Filesystem::GetExeVersion(path)};
        }

        path = m_path / "win32" / L"WorldOfTanks.exe";
        if (Common::Filesystem::Exists(path)) {
            return {Common::Filesystem::GetExeVersion(path)};
        }

        path = m_path / L"WorldOfTanks.exe";
        if (Common::Filesystem::Exists(path)) {
            return {Common::Filesystem::GetExeVersion(path)};
        }

        return std::nullopt;
    }

    //
    // Private
    //

    std::optional<std::wstring> ClientWoT::getVersionClientRaw() {
        auto versionxml = m_path / L"version.xml";
        if (!Common::Filesystem::Exists(versionxml)) {
            return std::nullopt;
        }

        pugi::xml_document doc;
        if (!doc.load_file(versionxml.wstring().c_str())) {
            return std::nullopt;
        }

        auto version = doc.select_node(L"/version.xml/version");
        if (!version) {
            return std::nullopt;
        }

        //get client version
        std::wstring result = version.node().first_child().value();
        result = Common::String::Trim(result);
        result = Common::String::Replace(result, L"v.", L"");
        if (result.find(L'#') != std::wstring::npos) {
            result = Common::String::Substring(result, 0, result.find(L'#'));
        }
        return {Common::String::Trim(result)};
    }



}
