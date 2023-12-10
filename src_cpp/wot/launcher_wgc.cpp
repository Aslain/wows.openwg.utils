#include <pugixml.hpp>

#include "fs/fs.h"
#include "common/vector.h"
#include "wot/client_wot.h"
#include "wot/launcher_wgc.h"

namespace OpenWG::Utils::WoT {
    LauncherWgc::LauncherWgc(const LauncherInfo &info, std::filesystem::path path_programdata,
                             std::filesystem::path path_wgc) : m_info(info),
                                                               m_path_programdata(std::move(path_programdata)),
                                                               m_path_wgc(std::move(path_wgc)) {

    }

    bool LauncherWgc::AddClient(const std::filesystem::path &path) {
        return false;
    }

    std::vector<std::shared_ptr<ClientInterface>> LauncherWgc::GetClients() {
        return m_clients;
    }

    LauncherFlavour LauncherWgc::GetFlavour() const {
        return m_info.flavour;
    }

    size_t LauncherWgc::Rescan() {
        m_clients.clear();
        for (auto &client_path: getClientPaths()) {
            if (!Filesystem::Exists(client_path)) {
                continue;
            }

            auto client = std::make_shared<ClientWoT>(client_path, m_info.flavour);
            if (!client->IsValid()) {
                continue;
            }

            m_clients.push_back(client);
        }

        return m_clients.size();
    }

    //
    // Private
    //

    std::vector<std::filesystem::path> LauncherWgc::getClientPaths() {
        std::vector<std::filesystem::path> result{};

        // <WGC>/preferences.xml
        try {
            auto preferencesPath = m_path_wgc / L"preferences.xml";
            if (Filesystem::Exists(preferencesPath)) {
                pugi::xml_document doc;
                if (doc.load_file(preferencesPath.wstring().c_str())) {

                    //selected wot game
                    auto wot = doc.select_node(L"/protocol/application/games_manager/selectedGames/WOT");
                    if (wot) {
                        std::filesystem::path path = wot.node().first_child().value();
                        if (!Common::Vector::Contains(result, path)) {
                            result.emplace_back(path);
                        }
                    }

                    //process
                    auto games = doc.select_node(L"/protocol/application/games_manager/games");
                    if (games) {
                        for (auto &game: games.node()) {
                            auto workdir = game.select_node(L".//working_dir");
                            if (!workdir) {
                                continue;
                            }

                            std::filesystem::path path = workdir.node().first_child().value();
                            if (!Common::Vector::Contains(result, path)) {
                                result.emplace_back(path);
                            }
                        }
                    }
                }
            }
        }
        catch (const std::exception &) {}

        // ProgramData
        try {
            for (auto &appinfo_folder: std::filesystem::directory_iterator(m_path_programdata / L"apps")) {
                if (appinfo_folder.path().filename().string().find("wot.") != 0) {
                    continue;
                }

                for (auto &appinfo_file: std::filesystem::directory_iterator(appinfo_folder)) {
                    std::filesystem::path path = Filesystem::GetFileContent(appinfo_file.path().wstring());
                    if (!Common::Vector::Contains(result, path)) {
                        result.emplace_back(path);
                    }
                }
            }
        }
        catch (const std::exception &) {}

        return result;
    }

    std::filesystem::path LauncherWgc::getPreferredPath() {
        auto preferencesPath = m_path_wgc / L"preferences.xml";
        if (!Filesystem::Exists(preferencesPath)) {
            return {};
        }

        pugi::xml_document doc;
        if (!doc.load_file(preferencesPath.wstring().c_str())) {
            return {};
        }

        auto wot = doc.select_node(L"/protocol/application/games_manager/selectedGames/WOT");
        if (!wot) {
            return {};
        }

        return {wot.node().first_child().value()};
    }
}
