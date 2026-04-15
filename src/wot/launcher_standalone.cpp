//
// Includes
//

// stdlib
#include <array>

// windows
#if defined(_WIN32)
#include <Windows.h>
#endif

// openwg.utils
#include "fs/fs.h"
#include "wine/wine.h"
#include "wot/client_wot.h"
#include "wot/launcher_standalone.h"



//
// Implementation
//

namespace OpenWG::Utils::WoT {

    std::vector<std::shared_ptr<ClientInterface>> LauncherStandalone::GetClients() {
        return m_clients;
    }

    LauncherFlavour LauncherStandalone::GetFlavour() const {
        return Launcher_Flavour_Standalone;
    }

    bool LauncherStandalone::AddClient(const std::filesystem::path& path) {
        return AddClient(path, GetFlavour());
    }

    bool LauncherStandalone::AddClient(const std::filesystem::path& path, LauncherFlavour flavour) {
        auto client = std::make_shared<ClientWoT>(path, flavour);
        if (!client || !client->IsValid()) {
            return false;
        }
        return AddClient(client);
    }

    bool LauncherStandalone::AddClient(const std::shared_ptr<ClientWoT>& client) {
        if(!client || !client->IsValid()){
            return false;
        }

        m_clients.push_back(client);
        return true;
    }


    size_t LauncherStandalone::Rescan() {
        m_clients.clear();

        // DRIVE:\Games\World_of_Warships*
		std::vector<std::wstring> pathes{
			L"",
			L"Games\\",
			L"Games\\Wargaming.net\\",
			L"Gry\\",
			L"Gry\\Steam\\steamapps\\common\\",
			L"Spiele\\",
			L"Spiele\\Steam\\steamapps\\common\\",
			L"Jeux\\",
			L"Jeux\\Steam\\steamapps\\common\\",
			L"Juegos\\",
			L"Juegos\\Steam\\steamapps\\common\\",
			L"Giochi\\",
			L"Giochi\\Steam\\steamapps\\common\\",
			L"Jogos\\",
			L"Jogos\\Steam\\steamapps\\common\\",
			L"Игры\\",
			L"Игры\\Steam\\steamapps\\common\\",
			L"SteamLibrary\\steamapps\\common\\",
			L"Steam\\steamapps\\common\\",
			L"Program Files (x86)\\Steam\\steamapps\\common\\",
			L"Program Files\\Steam\\steamapps\\common\\"
		};

        for (auto& drive : Filesystem::GetLogicalDrives()) {
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

                        std::wstring dirname = p.path().filename().wstring();
                        if (dirname.find(L"World_of_Warships") == 0 || dirname.find(L"World of Warships") == 0) {
                            LauncherFlavour flavour = Launcher_Flavour_Standalone;
                            std::wstring path_str = p.path().wstring();
                            std::transform(path_str.begin(), path_str.end(), path_str.begin(), ::tolower);
                            if (path_str.find(L"steam") != std::wstring::npos) {
                                flavour = Launcher_Flavour_Steam;
                            }
                            AddClient(p.path(), flavour);
                        }
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
#if defined(_WIN32)
            GetEnvironmentVariableW(L"USERNAME", buf.data(), 256);
#endif
            std::wstring wot_osx = std::wstring(L"Z:\\Users\\") + std::wstring(buf.data()) + std::wstring(
                    L"\\Library\\Application Support\\World of Warships\\Bottles\\worldofWarships\\drive_c\\Games\\World_of_Warships\\");
            if (Filesystem::Exists(wot_osx)) {
                AddClient(wot_osx);
            }
        }

        return m_clients.size();
    }



}