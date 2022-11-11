#pragma once

//
// Includes
//

#include <cstddef>
#include <string>

#include "module_wot/api_wot.h"
#include "module_wot/client_interface.h"


//
// Interfaces
//

namespace OpenWG::Utils::WoT {
    /**
     * Structure which describes launcher info
     */
    struct LauncherInfo {
        /**
         * flavour of the launcher (WGC, Steam, ...)
         */
        LauncherFlavour flavour;

        /**
         * path to the WGC data, relative to %PROGRAMDATA%
         */
        std::wstring prefix;

        /**
         * path to the file with the real launcher location, relative to prefix
         */
        std::wstring path_filename;

        /**
         * name of WGC main executable, with extension
         */
        std::wstring exe_filename;
    };

    class LauncherInterface {
    public:
        virtual ~LauncherInterface() = default;

        [[nodiscard]] virtual std::vector<std::shared_ptr<ClientInterface>> GetClients()  = 0;

        [[nodiscard]] virtual LauncherFlavour GetFlavour() const = 0;

        /**
         * Scan launcher for available clients
         * @return number of clients found
         */
        virtual size_t Rescan() = 0;
    };
}
