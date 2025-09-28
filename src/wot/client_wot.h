#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "wot/api_wot.h"
#include "wot/client_interface.h"
#include "wot/client_version.h"

namespace OpenWG::Utils::WoT {
    class ClientWoT : public ClientInterface {
    public:
        ~ClientWoT() override;

        struct PackageDefinition {
            std::wstring relativePath{};
            std::vector<std::wstring> types{};
        };

        ClientWoT(std::filesystem::path path, LauncherFlavour launcherFlavour);

    public:
        [[nodiscard]] bool IsValid() const override;

        [[nodiscard]] ClientBranch GetBranch() const override;

        [[nodiscard]] std::wstring GetExeName() const override;

        [[nodiscard]] LauncherFlavour GetLauncherFlavour() const override;

        [[nodiscard]] std::wstring GetLocale() const override;

        [[nodiscard]] std::filesystem::path GetPath() const override;

        [[nodiscard]] std::wstring GetPathMods() const override;
 
        [[nodiscard]] std::wstring GetPathResmods() const override;
 
        [[nodiscard]] const std::vector<PackageDefinition>& GetPackages() const;

        [[nodiscard]] bool ExtractPackageFileToFile(const std::wstring& package_relative_path,
                                                    const std::wstring& entry_path,
                                                    const std::filesystem::path& destination) override;

        [[nodiscard]] bool ExtractPackageFileToMemory(const std::wstring& package_relative_path,
                                                      const std::wstring& entry_path,
                                                      void* destination,
                                                      uint64_t destination_size,
                                                      uint64_t* bytes_written) override;

        [[nodiscard]] std::wstring GetRealm() const override;

        [[nodiscard]] ClientType GetType() const override;

        [[nodiscard]] ClientVendor GetVendor() const override;

        [[nodiscard]] std::wstring GetVersionClient() const override;

        [[nodiscard]] std::wstring GetVersionExe() const override;

        [[nodiscard]] bool IsStarted() const override;

        [[nodiscard]] bool IsVersionMatch(const std::wstring& pattern) const override;

        bool Terminate() override;

        // Cache

        [[nodiscard]] ClientCache GetCacheSupported() const override;

        [[nodiscard]] ClientCache GetCachePresent() const override;

        [[nodiscard]] bool ClearCache(ClientCache cache_type) override;

    private:
        bool isValid(bool skip_exe);

        void rescan();

        void rescanAppType();

        void rescanExe();

        void rescanPaths();

        void rescanGameInfo();

        void rescanVersion();


    private:
        ClientBranch m_branch{ClientBranch::WoT_Branch_Unknown};
        LauncherFlavour m_launcherFlavour{Launcher_Flavour_Unknown};
        ClientVendor m_vendor{ClientVendor::WoT_Vendor_Unknown};
        std::wstring m_locale{};
        std::wstring m_exe_name{};
        std::filesystem::path m_path{};
        std::wstring m_path_mods{};
        std::wstring m_path_resmods{};
        std::vector<PackageDefinition> m_packages{};
        std::wstring m_realm{};
        ClientType m_type{ClientType::WoT_Type_Unknown};
        ClientVersion m_versionClient{};
        std::wstring m_versionExe{};
        bool m_valid{ false };

        [[nodiscard]] std::filesystem::path resolvePackagePath(const std::wstring& package_relative_path) const;

    };
}
