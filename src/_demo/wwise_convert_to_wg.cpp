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
    std::cout << "OpenWG.Utils: WWISE license converter" << std::endl;
    std::cout << "Converting " << argc - 1 << " files" << std::endl;
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
        if (license == WwiseLicense_Wargaming) {
            std::cout << "    - SKIP, license is equal to Wargaming.net" << std::endl;
            WWISE_Close(wwise);
            continue;
        }
        if (license != WwiseLicense_Unlicensed) {
            std::cout << "    - FAIL, cannot detect the license" << std::endl;
            WWISE_Close(wwise);
            continue;
        }
        if (!WWISE_LicenseSet(wwise, WwiseLicense_Wargaming)) {
            std::cout << "    - FAIL, cannot change the license" << std::endl;
            WWISE_Close(wwise);
            continue;
        }
        if (!WWISE_SaveFileW(wwise, filepath.wstring().c_str())) {
            std::cout << "    - FAIL, cannot save the changes" << std::endl;
            WWISE_Close(wwise);
            continue;
        }

        std::cout << "    - OK" << std::endl;
        WWISE_Close(wwise);
    }

    std::cout << std::endl << "---" << std::endl << "press Enter to exit" << std::endl;
    std::cin.get();
    return 0;
}