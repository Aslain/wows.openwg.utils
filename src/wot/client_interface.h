#pragma once

#include <filesystem>
#include <string>

#include "api_wot.h"

namespace OpenWG::Utils::WoT {
    class ClientInterface{
    public:
        virtual ~ClientInterface() = default;

        [[nodiscard]] virtual bool IsValid() const = 0;

        [[nodiscard]] virtual ClientBranch GetBranch() const = 0;

        [[nodiscard]] virtual std::wstring GetExeName() const = 0;

        [[nodiscard]] virtual LauncherFlavour GetLauncherFlavour() const = 0;

        [[nodiscard]] virtual std::wstring GetLocale() const = 0;

        [[nodiscard]] virtual std::filesystem::path GetPath() const = 0;

        [[nodiscard]] virtual std::wstring GetPathMods() const = 0;

        [[nodiscard]] virtual std::wstring GetPathResmods() const = 0;

        [[nodiscard]] virtual std::wstring GetRealm() const = 0;

        [[nodiscard]] virtual ClientType GetType() const = 0;

        [[nodiscard]] virtual ClientVendor GetVendor() const = 0;

        [[nodiscard]] virtual std::wstring GetVersionClient() const = 0;

        [[nodiscard]] virtual std::wstring GetVersionExe() const = 0;

        [[nodiscard]] virtual bool IsStarted() const = 0;

        [[nodiscard]] virtual bool IsVersionMatch(const std::wstring& pattern) const = 0;

        virtual bool Terminate() = 0;

    };
}
