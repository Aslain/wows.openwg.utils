#pragma once

#include <filesystem>
#include <optional>
#include <string>

#include "api_wot.h"

namespace OpenWG::Utils::WoT {
    class ClientInterface{
    public:
        virtual ~ClientInterface() = default;

        virtual bool IsValid() = 0;

        virtual ClientBranch GetBranch() = 0;

        virtual LauncherFlavour GetLauncherFlavour() = 0;

        virtual std::optional<std::wstring> GetLocale() = 0;

        virtual std::filesystem::path GetPath() = 0;

        virtual std::optional<std::wstring> GetRealm() = 0;

        virtual ClientType GetType() = 0;

        virtual std::optional<std::wstring> GetVersionClient() = 0;

        virtual std::optional<std::wstring> GetVersionExe() = 0;

        virtual bool IsStarted() = 0;

        virtual bool Terminate() = 0;

    };
}
