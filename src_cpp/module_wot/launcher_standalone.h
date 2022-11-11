#pragma once

#include <memory>
#include <vector>

#include "client_interface.h"
#include "launcher_interface.h"

namespace OpenWG::Utils::WoT {
    class LauncherStandalone : public LauncherInterface{
    public:
        LauncherStandalone() = default;

        [[nodiscard]]  std::vector<std::shared_ptr<ClientInterface>> GetClients() override;

        [[nodiscard]] LauncherFlavour GetFlavour() const override;

        size_t Rescan() override;

    public:
        bool AddClient(const std::filesystem::path& path);

    private:
        std::vector<std::wstring> getDrives();

    private:
        std::vector<std::shared_ptr<ClientInterface>> m_clients{};
    };
}