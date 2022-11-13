#include <regex>

#include <pugixml.hpp>

#include "common/filesystem.h"
#include "common/string.h"
#include "module_process/process_module.h"
#include "module_wot/client_wot.h"

namespace OpenWG::Utils::WoT {

    ClientWoT::ClientWoT(std::filesystem::path path, LauncherFlavour launcherFlavour) : m_path(path.lexically_normal()),
                                                                                        m_launcherFlavour(
                                                                                                launcherFlavour) {
        rescan();
    }


    bool ClientWoT::IsValid() const {
        return Common::Filesystem::Exists(m_path / "app_type.xml") &&
               Common::Filesystem::Exists(m_path / "game_info.xml") &&
               Common::Filesystem::Exists(m_path / "paths.xml") &&
               Common::Filesystem::Exists(m_path / "version.xml") &&
               Common::Filesystem::Exists(m_path / m_exename);
    }

    ClientBranch ClientWoT::GetBranch() const {
        return m_branch;
    }

    LauncherFlavour ClientWoT::GetLauncherFlavour() const {
        return m_launcherFlavour;
    }

    std::wstring ClientWoT::GetLocale() const {
        return m_locale;
    }

    std::filesystem::path ClientWoT::GetPath() const {
        return m_path;
    }

    std::wstring ClientWoT::GetRealm() const {
        return m_realm;
    }

    ClientType ClientWoT::GetType() const {
        return m_type;
    }

    std::wstring ClientWoT::GetPathMods() const {
        return m_path_mods;
    }

    std::wstring ClientWoT::GetPathResmods() const {
        return m_path_resmods;
    }

    std::wstring ClientWoT::GetVersionClient() const {
        return m_versionClient;
    }

    std::wstring ClientWoT::GetVersionExe() const {
        return m_versionExe;
    }

    bool ClientWoT::IsStarted() const {
        bool result{false};
        for (auto &process: Process::GetProcessList()) {
            if (Common::Filesystem::IsSubpath(process.first, GetPath())) {
                auto process_name = Common::String::ToLower(process.first.filename().wstring());
                if (process_name == Common::String::ToLower(m_exename)) {
                    result = true;
                    break;
                }
            }
        }

        return result;
    }

    bool ClientWoT::IsVersionMatch(const std::wstring &pattern) const {
        std::wregex regex(pattern);
        std::wsmatch match;
        return std::regex_match(m_versionClient.begin(), m_versionClient.end(), match, regex);
    }

    bool ClientWoT::Terminate() {
        bool result{false};
        for (auto &process: Process::GetProcessList()) {
            if (Common::Filesystem::IsSubpath(process.first, GetPath())) {
                auto process_name = Common::String::ToLower(process.first.filename().wstring());
                if (process_name == Common::String::ToLower(m_exename)) {
                    result = Process::TerminateProcess(process.second);
                }
            }
        }

        return result;
    }

    //
    // Private
    //

    void ClientWoT::rescan() {
        if (!IsValid()) {
            return;
        }

        rescanAppType();
        rescanExe();
        rescanGameInfo();
        rescanPaths();
        rescanVersion();
    }

    void ClientWoT::rescanAppType() {
        m_type = WoT_Type_Unknown;
        auto apptypexml = m_path / L"app_type.xml";
        if (Common::Filesystem::Exists(apptypexml)) {

            pugi::xml_document doc;
            if (!doc.load_file(apptypexml.wstring().c_str())) {
                m_type = WoT_Type_Unknown;
            }

            auto apptype = doc.select_node(L"/protocol/app_type");
            if (apptype) {
                std::wstring value = apptype.node().first_child().value();
                if (value == L"sd") {
                    m_type = WoT_Type_SD;
                } else if (value == L"hd") {
                    m_type = WoT_Type_HD;
                }
            }
        }
    }

    void ClientWoT::rescanExe() {
        m_versionExe.clear();

        auto path = m_path / "win64" / m_exename;
        if (Common::Filesystem::Exists(path)) {
            m_versionExe = Common::Filesystem::GetExeVersion(path);
            return;
        }

        path = m_path / "win32" / m_exename;
        if (Common::Filesystem::Exists(path)) {
            m_versionExe = Common::Filesystem::GetExeVersion(path);
            return;
        }

        path = m_path / m_exename;
        if (Common::Filesystem::Exists(path)) {
            m_versionExe = Common::Filesystem::GetExeVersion(path);
            return;
        }
    }

    void ClientWoT::rescanGameInfo() {
        m_locale.clear();
        auto gameinfoxml = m_path / L"game_info.xml";
        if (Common::Filesystem::Exists(gameinfoxml)) {

            pugi::xml_document doc;
            if (doc.load_file(gameinfoxml.wstring().c_str())) {

                auto localization = doc.select_node(L"/protocol/game/localization");
                if (localization) {
                    m_locale = localization.node().first_child().value();
                }
            }
        }
    }

    void ClientWoT::rescanPaths() {
        m_path_mods.clear();
        m_path_resmods.clear();

        auto pathsxml = m_path / L"paths.xml";
        if (Common::Filesystem::Exists(pathsxml)) {
            pugi::xml_document doc;
            if (doc.load_file(pathsxml.wstring().c_str())) {
                auto nodes = doc.select_nodes(L"/root/Paths/Path");
                for (auto node: nodes) {
                    std::wstring path = node.node().first_child().value();
                    path = Common::String::Replace(path, L"/", L"\\");
                    path = Common::String::Replace(path, L".\\", L"");

                    if (m_path_resmods.empty() && path.starts_with(L"res_mods\\")) {
                        m_path_resmods = path;
                    } else if (m_path_mods.empty() && path.starts_with(L"mods\\")) {
                        m_path_mods = path;
                    }
                }
            }
        }
    }

    void ClientWoT::rescanVersion() {
        m_branch = ClientBranch::WoT_Branch_Unknown;
        m_realm.clear();

        auto versionxml = m_path / L"version.xml";
        if (Common::Filesystem::Exists(versionxml)) {
            pugi::xml_document doc;
            if (doc.load_file(versionxml.wstring().c_str())) {
                // realm
                auto realm = doc.select_node(L"/version.xml/meta/realm");
                if (realm) {
                    m_realm = Common::String::Trim(realm.node().first_child().value());
                }

                // version & branch
                auto version = doc.select_node(L"/version.xml/version");
                if (version) {

                    //get client raw version
                    std::wstring version_raw = version.node().first_child().value();
                    version_raw = Common::String::Trim(version_raw);
                    version_raw = Common::String::Replace(version_raw, L"v.", L"");
                    if (version_raw.find(L'#') != std::wstring::npos) {
                        version_raw = Common::String::Substring(version_raw, 0, version_raw.find(L'#'));
                    }
                    version_raw = Common::String::Trim(version_raw);

                    //tokenize
                    auto version_tokens = Common::String::Split(version_raw, L' ', 2);

                    //version client
                    m_versionClient = Common::String::Trim(version_tokens[0]);

                    //branch
                    std::wstring type{};
                    if (version_tokens.size() == 2) {
                        type = Common::String::Trim(version_tokens[1]);
                    }
                    if (type.empty()) {
                        m_branch = WoT_Branch_Release;
                    } else if (type == L"Common Test") {
                        m_branch = WoT_Branch_CommonTest;
                    } else if (type == L"ST") {
                        m_branch = WoT_Branch_SuperTest;
                    } else if (type == L"SB") {
                        m_branch = WoT_Branch_Sandbox;
                    }
                }
            }
        }
    }

}
