#pragma once

#include <memory>
#include <vector>

#include "launcher_interface.h"

namespace OpenWG::Utils::WoT {
    namespace LauncherFactory {
        std::vector<std::shared_ptr<LauncherInterface>> getLaunchers(LauncherFlavour default_flavour);
    }
}
