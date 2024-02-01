#pragma once

#include <string>

#include "wot/api_wot.h"
#include "wot/client_interface.h"

namespace OpenWG::Utils::WoT {
    class ClientWoT : public ClientInterface {
    public:
        ClientWoT(std::filesystem::path path, LauncherFlavour launcherFlavour);

    public:
        [[nodiscard]] bool IsValid() const override;

        [[nodiscard]] ClientBranch GetBranch() const override;

        [[nodiscard]] LauncherFlavour GetLauncherFlavour() const override;

        [[nodiscard]] std::wstring GetLocale() const override;

        [[nodiscard]] std::filesystem::path GetPath() const override;

        [[nodiscard]] std::wstring GetPathMods() const override;

        [[nodiscard]] std::wstring GetPathResmods() const override;

        [[nodiscard]] std::wstring GetRealm() const override;

        [[nodiscard]] ClientType GetType() const override;

        [[nodiscard]] ClientVendor GetVendor() const override;

        [[nodiscard]] std::wstring GetVersionClient() const override;

        [[nodiscard]] std::wstring GetVersionExe() const override;

        [[nodiscard]] bool IsStarted() const override;

        [[nodiscard]] bool IsVersionMatch(const std::wstring& pattern) const override;

        bool Terminate() override;

    private:
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
        std::filesystem::path m_path{};
        std::wstring m_path_mods{};
        std::wstring m_path_resmods{};
        std::wstring m_realm{};
        ClientType m_type{ClientType::WoT_Type_Unknown};
        std::wstring m_versionClient{};
        std::wstring m_versionExe{};

    private:
        static constexpr auto m_exename = L"WorldOfTanks.exe";
    };
}
