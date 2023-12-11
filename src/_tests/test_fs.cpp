// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

//
// Includes
//

#include <filesystem>
#include <catch2/catch_test_macros.hpp>
#include "fs/api_fs.h"



//
// Test
//

TEST_CASE( "fs_file_isEqual", "[fs]" ) {
    SECTION("nullptr") {
        REQUIRE_FALSE(FS_File_IsEqualW(nullptr, nullptr));
        REQUIRE_FALSE(FS_File_IsEqualW(L"m", nullptr));
        REQUIRE_FALSE(FS_File_IsEqualW(nullptr, L"k"));
    }

    SECTION("equal") {
        REQUIRE(
                FS_File_IsEqualW(
                        (std::filesystem::path(ASSETS_FOLDER) / "engine_config.xml").wstring().c_str(),
                        (std::filesystem::path(ASSETS_FOLDER) / "engine_config.xml").wstring().c_str()
                )
        );
    }

    SECTION("not_equal") {
        REQUIRE_FALSE(
                FS_File_IsEqualW(
                        (std::filesystem::path(ASSETS_FOLDER) / "engine_config.xml").wstring().c_str(),
                        (std::filesystem::path(ASSETS_FOLDER) / "u_wg.bnk").wstring().c_str()
                )
        );
    }
}
