#pragma once

#include <memory>
#include <vector>

#include "client_interface.h"
#include "launcher_interface.h"
#include "client_wot.h"

namespace OpenWG::Utils::WoT {
    class LauncherStandalone : public LauncherInterface {
    public:
        LauncherStandalone() = default;

        // LauncherInterface
    public:
        [[nodiscard]]  std::vector<std::shared_ptr<ClientInterface>> GetClients() override;

        [[nodiscard]] LauncherFlavour GetFlavour() const override;

        size_t Rescan() override;

        bool AddClient(const std::filesystem::path &path) override;

        // LauncherStandalone
        bool AddClient(const std::shared_ptr<ClientWoT>& client);


    private:
        std::vector<std::shared_ptr<ClientInterface>> m_clients{};
    };
}