#include <regex>

#include <pugixml.hpp>

#include "fs/fs.h"
#include "string/string.h"
#include "process/process_module.h"
#include "wot/client_wot.h"

namespace OpenWG::Utils::WoT {

    ClientWoT::ClientWoT(std::filesystem::path path, LauncherFlavour launcherFlavour) : m_path(path.lexically_normal()),
                                                                                        m_launcherFlavour(launcherFlavour) {
        rescan();
    }

    ClientWoT::~ClientWoT() = default;


    bool ClientWoT::IsValid() const {
        return m_valid;
    }

    ClientBranch ClientWoT::GetBranch() const {
        return m_branch;
    }

    std::wstring ClientWoT::GetExeName() const
    {
        return m_exe_name;
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

    ClientVendor ClientWoT::GetVendor() const {
        return m_vendor;
    }

    std::wstring ClientWoT::GetPathMods() const {
        return m_path_mods;
    }

    std::wstring ClientWoT::GetPathResmods() const {
        return m_path_resmods;
    }

    const std::vector<ClientWoT::PackageDefinition>& ClientWoT::GetPackages() const {
        return m_packages;
    }

    std::wstring ClientWoT::GetVersionClient() const {
        return m_versionClient.Get();
    }

    std::wstring ClientWoT::GetVersionExe() const {
        return m_versionExe;
    }

    bool ClientWoT::IsStarted() const {
        bool result{false};
        for (auto &process: Process::GetProcessList()) {
            if (Filesystem::IsSubpath(process.first, GetPath())) {
                auto process_name = String::ToLower(process.first.filename().wstring());
                if (process_name == String::ToLower(m_exe_name)) {
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
        return std::regex_match(m_versionClient.Get().begin(), m_versionClient.Get().end(), match, regex);
    }

    bool ClientWoT::Terminate() {
        bool result{false};
        for (auto &process: Process::GetProcessList()) {
            if (Filesystem::IsSubpath(process.first, GetPath())) {
                auto process_name = String::ToLower(process.first.filename().wstring());
                if (process_name == String::ToLower(m_exe_name)) {
                    result = Process::TerminateProcess(process.second);
                }
            }
        }

        return result;
    }

    //
    // Public/Cache
    //

    ClientCache ClientWoT::GetCacheSupported() const
    {
        ClientCache cache{};

        if (GetVendor() == WoT_Vendor_WG) {
            if (m_versionClient >= ClientVersion(L"1.27.1") || std::filesystem::exists(GetPath() / L"data.wgpdc"))
            {
                cache = cache | WoT_Cache_PDC;
            }
        }

        return cache;
    }

    ClientCache ClientWoT::GetCachePresent() const
    {
        ClientCache result{};

        if ((GetCacheSupported() & WoT_Cache_PDC) == WoT_Cache_PDC)
        {
            if (std::filesystem::exists(GetPath() / L"data.wgpdc"))
            {
                result = result | WoT_Cache_PDC;
            }
        }

        return result;
    }

    bool ClientWoT::ClearCache(ClientCache cache_type)
    {
        bool result{};

        if ((cache_type & WoT_Cache_PDC) == WoT_Cache_PDC && (GetCachePresent() & WoT_Cache_PDC) == WoT_Cache_PDC)
        {
            result = std::filesystem::remove(GetPath() / L"data.wgpdc");
        }

        return result;
    }

    //
    // Private
    //

    bool ClientWoT::isValid(bool skip_exe)
    {
        bool valid = Filesystem::Exists(m_path) &&
            Filesystem::Exists(m_path / "app_type.xml") &&
            Filesystem::Exists(m_path / "game_info.xml") &&
            Filesystem::Exists(m_path / "paths.xml") &&
            Filesystem::Exists(m_path / "version.xml");
        
        if (!skip_exe) {
            if (m_exe_name.empty()) {
                valid = false;
            }
            else {
                valid = Filesystem::Exists(m_path / m_exe_name);
            }
        }
        
        return valid;
    }

    void ClientWoT::rescan() {
        m_valid = false;

        if (!isValid(true)) {
            return;
        }

        rescanAppType();
        rescanVersion();
        rescanExe();

        if (!isValid(false)) {
            return;
        }

        rescanGameInfo();
        rescanPaths();

        m_valid = true;
    }

    void ClientWoT::rescanAppType() {
        m_type = WoT_Type_Unknown;
        auto apptypexml = m_path / L"app_type.xml";
        if (Filesystem::Exists(apptypexml)) {

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
        m_exe_name.clear();

        if (m_vendor == WoT_Vendor_Lesta && m_versionClient >= ClientVersion(L"1.32.0.0")) {
            m_exe_name = L"Tanki.exe";
        }
        else {
            m_exe_name = L"WorldOfTanks.exe";
        }

        auto path = m_path / "win64" / m_exe_name;
        if (Filesystem::Exists(path)) {
            m_versionExe = Filesystem::GetExeVersion(path.wstring());
            return;
        }

        path = m_path / "win32" / m_exe_name;
        if (Filesystem::Exists(path)) {
            m_versionExe = Filesystem::GetExeVersion(path.wstring());
            return;
        }

        path = m_path / m_exe_name;
        if (Filesystem::Exists(path)) {
            m_versionExe = Filesystem::GetExeVersion(path.wstring());
            return;
        }
    }

    void ClientWoT::rescanGameInfo() {
        m_locale.clear();
        auto gameinfoxml = m_path / L"game_info.xml";
        if (Filesystem::Exists(gameinfoxml)) {

            pugi::xml_document doc;
            if (doc.load_file(gameinfoxml.wstring().c_str())) {
                // id
                auto id = doc.select_node(L"/protocol/game/id");
                if (id) {
                    std::wstring id_str = id.node().first_child().value();
                    if (id_str.contains(L".RPT.")) {
                        m_branch = ClientBranch::WoT_Branch_CommonTest;
                    }
                }

                // localization
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
        m_packages.clear();

        auto normalizeRelativePath = [](std::wstring value) {
            value = String::Trim(value);
            value = String::Replace(value, L"\\", L"/");
            while (value.starts_with(L"./")) {
                value = value.substr(2);
            }
            return value;
        };

        auto pathsxml = m_path / L"paths.xml";
        if (Filesystem::Exists(pathsxml)) {
            pugi::xml_document doc;
            if (doc.load_file(pathsxml.wstring().c_str())) {
                auto pathNodes = doc.select_nodes(L"/root/Paths/Path");
                for (const auto& pathNode : pathNodes) {
                    const auto& xmlNode = pathNode.node();
                    std::wstring relativePath = normalizeRelativePath(std::wstring(xmlNode.text().as_string()));
                    if (relativePath.empty()) {
                        continue;
                    }

                    if (m_path_resmods.empty() && relativePath.starts_with(L"res_mods/")) {
                        m_path_resmods = relativePath;
                    } else if (m_path_mods.empty() && relativePath.starts_with(L"mods/")) {
                        m_path_mods = relativePath;
                    }
                }

                auto packageNodes = doc.select_nodes(L"/root/Paths/Packages/Package");
                for (const auto& packageNode : packageNodes) {
                    const auto& xmlNode = packageNode.node();
                    std::wstring relativePath = normalizeRelativePath(std::wstring(xmlNode.text().as_string()));
                    if (relativePath.empty()) {
                        continue;
                    }

                    PackageDefinition definition{};
                    definition.relativePath = relativePath;

                    if (auto attribute = xmlNode.attribute(L"type")) {
                        auto tokens = String::Split(std::wstring(attribute.as_string()), L',');
                        definition.types.reserve(tokens.size());
                        for (auto& token : tokens) {
                            std::wstring trimmed = String::Trim(token);
                            if (!trimmed.empty()) {
                                definition.types.emplace_back(trimmed);
                            }
                        }
                    }

                    m_packages.emplace_back(definition);
                }
            }
        }
    }

    void ClientWoT::rescanVersion() {
        m_branch = ClientBranch::WoT_Branch_Unknown;
        m_realm.clear();

        auto versionxml = m_path / L"version.xml";
        if (Filesystem::Exists(versionxml)) {
            pugi::xml_document doc;
            if (doc.load_file(versionxml.wstring().c_str())) {
                // realm
                auto realm = doc.select_node(L"/version.xml/meta/realm");
                if (realm) {
                    m_realm = String::Trim(realm.node().first_child().value());
                    m_vendor = (m_realm == L"RU" || m_realm == L"RPT") ? WoT_Vendor_Lesta : WoT_Vendor_WG;
                }

                // version & branch
                auto version = doc.select_node(L"/version.xml/version");
                if (version) {

                    //get client raw version
                    std::wstring version_raw = version.node().first_child().value();
                    version_raw = String::Trim(version_raw);
                    version_raw = String::Replace(version_raw, L"v.", L"");
                    if (version_raw.find(L'#') != std::wstring::npos) {
                        version_raw = String::Substring(version_raw, 0, version_raw.find(L'#'));
                    }
                    version_raw = String::Trim(version_raw);

                    //tokenize
                    auto version_tokens = String::Split(version_raw, L' ', 2);

                    //version client
                    m_versionClient = String::Trim(version_tokens[0]);

                    //branch
                    std::wstring type{};
                    if (version_tokens.size() == 2) {
                        type = String::Trim(version_tokens[1]);
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
                    else if (type == L"Test") {
                        if (version_tokens[0] == L"Closed") {
                            m_branch = WoT_Branch_ClosedTest;
                        }
                    }
                    if(m_realm == L"RPT"){
                        m_branch  = WoT_Branch_CommonTest;
                    }
                }
            }
        }
    }

}
