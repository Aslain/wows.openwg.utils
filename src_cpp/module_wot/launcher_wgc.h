#pragma once

#include <filesystem>

#include "launcher_interface.h"
#include "client_interface.h"

namespace OpenWG::Utils::WoT {
    class LauncherWgc : public LauncherInterface{
    public:
        LauncherWgc(const LauncherInfo& info, std::filesystem::path path_programdata, std::filesystem::path path_wgc);

        [[nodiscard]]  std::vector<std::shared_ptr<ClientInterface>> GetClients() override;

        [[nodiscard]] LauncherFlavour GetFlavour() const override;

        size_t Rescan() override;

    private:
        std::vector<std::filesystem::path> getClientPaths();
        std::filesystem::path getPreferredPath();

    private:
        LauncherInfo m_info;
        std::filesystem::path m_path_programdata{};
        std::filesystem::path m_path_wgc{};

        std::vector<std::shared_ptr<ClientInterface>> m_clients;
    };
}