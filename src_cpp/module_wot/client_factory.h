#pragma once

#include <filesystem>
#include <memory>

#include "module_wot/client_interface.h"

namespace OpenWG::Utils::WoT {
    namespace ClientFactory {
        std::shared_ptr<ClientInterface> CreateClient(std::filesystem::path path);
    }
}
