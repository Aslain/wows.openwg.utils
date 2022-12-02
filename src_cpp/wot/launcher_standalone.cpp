#include <array>

#include <Windows.h>

#include "common/filesystem.h"
#include "wine/wine.h"
#include "wot/client_wot.h"
#include "wot/launcher_standalone.h"

namespace OpenWG::Utils::WoT {

    std::vector<std::shared_ptr<ClientInterface>> LauncherStandalone::GetClients() {
        return m_clients;
    }

    LauncherFlavour LauncherStandalone::GetFlavour() const {
        return Launcher_Flavour_Standalone;
    }

    bool LauncherStandalone::AddClient(const std::filesystem::path& path) {
        if (!exists(path)) {
            return false;
        }

        auto client = std::make_shared<ClientWoT>(path, GetFlavour());
        if (!client || !client->IsValid()) {
            return false;
        }

        m_clients.push_back(client);
        return true;
    }

    size_t LauncherStandalone::Rescan() {
        m_clients.clear();

        // DRIVE:\Games\World_of_Tanks*
        std::vector<std::wstring> pathes{L"", L"Games\\", L"Games\\Wargaming.net\\"};

        for (auto& drive : getDrives()) {
            for (auto &path: pathes) {
                try {
                    auto drive_path = drive + path;

                    if (!std::filesystem::exists(drive_path)) {
                        continue;
                    }

                    for (auto &p: std::filesystem::directory_iterator(drive_path)) {

                        if (!std::filesystem::is_directory(p)) {
                            continue;
                        }

                        AddClient(p.path());
                    }
                }
                catch (std::filesystem::filesystem_error &ex) {
                    continue;
                }
                catch (std::system_error &ex) {
                    continue;
                }
            }
        }

        // WoT OSX edition (Wargaming.net wine wrapper)
        if(Wine::GetStatus().running_on) {
            std::array<wchar_t, 256> buf{};
            GetEnvironmentVariableW(L"USERNAME", buf.data(), 256);

            std::wstring wot_osx = std::wstring(L"Z:\\Users\\") + std::wstring(buf.data()) + std::wstring(
                    L"\\Library\\Application Support\\World of Tanks\\Bottles\\worldoftanks\\drive_c\\Games\\World_of_Tanks\\");
            if (Common::Filesystem::Exists(wot_osx)) {
                AddClient(wot_osx);
            }
        }

        return m_clients.size();
    }

    std::vector<std::wstring> LauncherStandalone::getDrives() {
        std::vector<std::wstring> drives = Common::Filesystem::GetLogicalDrives();

        // Non-windows additions
        Wine::WineStatus wine_status = Wine::GetStatus();
        if (wine_status.running_on) {
            std::array<wchar_t, 256> buf{};
            GetEnvironmentVariableW(L"USERNAME", buf.data(), 256);

            if (wcscmp(wine_status.system, L"Linux") == 0) {
                // /media/<USERNAME>/ mounted partitions
                std::wstring linux_mounts(
                        std::wstring(L"Z:\\media\\") + std::wstring(buf.data()) + std::wstring(L"\\"));
                if (Common::Filesystem::Exists(linux_mounts)) {
                    for (auto &p: std::filesystem::directory_iterator(linux_mounts)) {
                        if (!std::filesystem::is_directory(p))
                            continue;

                        drives.push_back(p.path().wstring() + L"\\");
                    }
                }
            }

            if (wcscmp(wine_status.system, L"Darwin") == 0) {
                // /Volumes/ mounted partitions
                if (Common::Filesystem::Exists(L"Z:\\Volumes\\")) {
                    for (auto &p: std::filesystem::directory_iterator(L"Z:\\Volumes\\")) {
                        if (!std::filesystem::is_directory(p))
                            continue;

                        drives.push_back(p.path().wstring() + L"\\");
                    }
                }
            }

        }

        return drives;
    }

}
