//
// Includes
//

// stdlib
#include <filesystem>
#include <iostream>

// openwg
#include "wwise/api_wwise.h"


//
// App
//

int main(int argc, char* argv[]) {
    std::cout << "OpenWG.Utils: WWISE Info" << std::endl;
    std::cout << "Processing " << argc - 1 << " files" << std::endl;
    for (size_t idx = 1; idx < argc; idx++) {
        std::filesystem::path filepath(argv[idx]);
        std::cout << " * " << filepath << std::endl;
        if (!std::filesystem::exists(filepath)) {
            std::cout << "    - FAIL, path does not exists" << std::endl;
            continue;
        }
        if (!std::filesystem::is_regular_file(filepath)) {
            std::cout << "    - FAIL, path is not a file" << std::endl;
            continue;
        }

        auto *wwise = WWISE_OpenFileW(filepath.wstring().c_str());
        if (!wwise) {
            std::cout << "    - FAIL, failed to open file" << std::endl;
            continue;
        }

        auto license = WWISE_LicenseGet(wwise);
        if (license == WwiseLicense_Unlicensed) {
            std::cout << "    - License = Unlicensed" << std::endl;
        }
        else if (license == WwiseLicense_Wargaming) {
            std::cout << "    - License = Wargaming" << std::endl;
        }
        else {
            std::cout << "    - License = Unknown" << std::endl;
            WWISE_Close(wwise);
            continue;
        }

        auto version = WWISE_VersionGet(wwise);
        std::string version_str;
        if (version == 135)
            version_str = "2019.2";
        else if (version == 150)
            version_str = "2023.1";
        else
            version_str = "Unknown";

        std::cout << "    - Version = " << version << " (" << version_str << ")" << std::endl;

        WWISE_Close(wwise);
    }

    std::cout << std::endl << "---" << std::endl << "press Enter to exit" << std::endl;
    std::cin.get();
    return 0;
}