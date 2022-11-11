#include "module_wot/client_factory.h"

namespace OpenWG::Utils::WoT {
    namespace ClientFactory {
        std::shared_ptr<ClientInterface> CreateClient(std::filesystem::path path) {
            return {};
        }
    }
}