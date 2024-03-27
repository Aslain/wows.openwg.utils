//
// Includes
//

// stdlib
#include <filesystem>
#include <iostream>

// openwg
#include "bwxml/api_bwxml.h"


//
// App
//

int wmain(int argc, wchar_t* argv[]) {
    std::cout << "OpenWG.Utils: BWXML unpacker" << std::endl;
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

        std::filesystem::path filepath_out = filepath;
        filepath_out.replace_extension("");
        filepath_out.replace_filename(filepath_out.filename() += L".unpacked.xml");

        if (BWXML_UnpackW(filepath.wstring().c_str(), filepath_out.wstring().c_str()) == 0) {
            std::cout << "    - OK" << std::endl;
        }
        else{
            std::cout << "    - FAIL" << std::endl;
        }
    }

    std::cout << std::endl << "---" << std::endl << "press Enter to exit" << std::endl;
    std::cin.get();
    return 0;
}