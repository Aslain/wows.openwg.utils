#include "common/filesystem.h"

#include "wgc_finder.h"

std::vector<std::pair<std::wstring, WgcFlavour>> WgcFinder::_programdata_suffixes = {
        {
                L"Wargaming.net//GameCenter", WgcFlavour::WG
        },
        {
                L"360 Wargaming//GameCenter", WgcFlavour::China360
        },
        {
                L"Wargaming.net//GameCenter for Steam", WgcFlavour::Steam
        }
};

std::vector<WgcClient> WgcFinder::GetWgcClients() {
    std::vector<WgcClient> result;

    auto program_data_path = Filesystem::GetProgramDataPath();
    for(auto& suffix : _programdata_suffixes){
        auto wgc_path_file = program_data_path / suffix.first / "data" / "wgc_path.dat";

        if (Filesystem::Exists(wgc_path_file)){
            auto wgc_path_content = std::filesystem::path(Filesystem::GetFileContent(wgc_path_file));
            if (Filesystem::Exists(wgc_path_content / "wgc.exe")){
                result.push_back(WgcClient(wgc_path_content, suffix.second));
            }
        }
    }

    return result;
}
