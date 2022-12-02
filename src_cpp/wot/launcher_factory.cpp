#include "common/filesystem.h"
#include "wot/launcher_factory.h"
#include "wot/launcher_standalone.h"
#include "wot/launcher_wgc.h"

namespace OpenWG::Utils::WoT {
    namespace LauncherFactory {

        //
        // Constants
        //

        std::vector<LauncherInfo> launchers_info{
                {
                        Launcher_Flavour_WG, L"Wargaming.net//GameCenter", L"wgc_path.dat", L"wgc.exe"
                },
                {
                        Launcher_Flavour_China360, L"360 Wargaming//GameCenter", L"wgc_path.dat", L"wgc.exe"
                },
                {
                        Launcher_Flavour_Steam, L"Wargaming.net//GameCenter for Steam", L"wgc_path.dat", L"wgc.exe"
                },
                {
                        Launcher_Flavour_Lesta, L"Lesta//GameCenter", L"lgc_path.dat", L"lgc.exe"
                },
                {
                        Launcher_Flavour_Standalone, L"", L"", L""
                },
        };

        //
        // Private
        //

        std::shared_ptr<LauncherInterface> getLauncher(const LauncherInfo& info) {
            if (info.flavour == Launcher_Flavour_Standalone) {
                return std::make_shared<LauncherStandalone>();
            } else {
                auto path_programdata = Common::Filesystem::GetProgramDataPath() / info.prefix;
                auto wgcpath_file = path_programdata / "data" / info.path_filename;

                if (Common::Filesystem::Exists(wgcpath_file)) {
                    auto path_wgc = std::filesystem::path(Common::Filesystem::GetFileContent(wgcpath_file));
                    if (Common::Filesystem::Exists(path_wgc / info.exe_filename)) {
                        return std::make_shared<LauncherWgc>(info, path_programdata, path_wgc);
                    }
                }
            }
            return {};
        }

        std::optional<LauncherInfo> getLauncherInfo(LauncherFlavour flavour) {
            for (auto &info: launchers_info) {
                if (info.flavour == flavour) {
                    return info;
                }
            }

            return std::nullopt;
        }

        //
        // Public
        //

        std::vector<std::shared_ptr<LauncherInterface>> getLaunchers(LauncherFlavour default_flavour) {
            std::vector<std::shared_ptr<LauncherInterface>> result{};

            //get default launcher
            auto info_default = getLauncherInfo(default_flavour);
            if (info_default.has_value()) {
                auto launcher = getLauncher(info_default.value());
                if (launcher) {
                    result.push_back(launcher);
                }
            }

            //process all the launchers
            for (auto &info: launchers_info) {
                //check for existing
                bool exists = false;
                for (auto &launcher: result) {
                    if (launcher && launcher->GetFlavour() == info.flavour) {
                        exists = true;
                        break;
                    }
                }
                if (exists) {
                    continue;
                }

                // add
                auto launcher = getLauncher(info);
                if (launcher) {
                    result.push_back(launcher);
                }
            }

            return result;
        }
    }
}