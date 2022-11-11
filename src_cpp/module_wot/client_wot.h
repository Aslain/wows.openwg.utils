#pragma once

#include <optional>
#include <string>

#include "module_wot/api_wot.h"
#include "module_wot/client_interface.h"

namespace OpenWG::Utils::WoT {
    class ClientWoT : public ClientInterface {
    public:
        ClientWoT(std::filesystem::path path, LauncherFlavour launcherFlavour);

    public:
        bool IsValid() override;

        ClientBranch GetBranch() override;

        LauncherFlavour GetLauncherFlavour() override;

        std::optional<std::wstring> GetLocale() override;

        std::filesystem::path GetPath() override;

        std::optional<std::wstring> GetRealm() override;

        ClientType GetType() override;

        std::optional<std::wstring> GetVersionClient() override;

        std::optional<std::wstring> GetVersionExe() override;

    private:
        std::optional<std::wstring> getVersionClientRaw();

    private:
        std::filesystem::path m_path{};
        LauncherFlavour m_launcherFlavour{Launcher_Flavour_Unknown};
    };
}