// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

//
// Includes
//

#include <filesystem>
#include <catch2/catch_test_macros.hpp>
#include "fs/api_fs.h"



//
// Test/File
//

TEST_CASE( "fs_file_isEqual", "[fs]" ) {
    SECTION("nullptr") {
        REQUIRE_FALSE(FS_FileEqualW(nullptr, nullptr));
        REQUIRE_FALSE(FS_FileEqualW(L"m", nullptr));
        REQUIRE_FALSE(FS_FileEqualW(nullptr, L"k"));
    }

    SECTION("equal") {
        REQUIRE(
                FS_FileEqualW(
                        (std::filesystem::path(ASSETS_FOLDER) / "engine_config.xml").wstring().c_str(),
                        (std::filesystem::path(ASSETS_FOLDER) / "engine_config.xml").wstring().c_str()
                )
        );
    }

    SECTION("not_equal") {
        REQUIRE_FALSE(
                FS_FileEqualW(
                        (std::filesystem::path(ASSETS_FOLDER) / "engine_config.xml").wstring().c_str(),
                        (std::filesystem::path(ASSETS_FOLDER) / "u_wg.bnk").wstring().c_str()
                )
        );
    }
}



//
// Test/Search
//

TEST_CASE( "fs_search", "[fs]" ) {
    SECTION("nullptr"){
        REQUIRE_FALSE(FS_Search_QueryFolderW(nullptr, 0));
        REQUIRE_FALSE(FS_Search_Close(nullptr));
        REQUIRE_FALSE(FS_Search_GetCount(nullptr));
        REQUIRE_FALSE(FS_Search_GetPathW(nullptr, 3, (wchar_t*)0x1234567, 1));
        REQUIRE_FALSE(FS_Search_GetPathW(reinterpret_cast<void *>(0x1234567), 3, nullptr, 1));
    }

    SECTION("system32-not-enough-depth"){
        wchar_t buf[256]{};
        auto obj = FS_Search_QueryFolderW(L"System32", 2);
        REQUIRE(obj);

        auto count = FS_Search_GetCount(obj);
        bool result = false;
        for(size_t idx = 0; idx < count; idx++) {
            auto buf_ret_size = FS_Search_GetPathW(obj, idx, buf, std::size(buf));
            REQUIRE(wcslen(buf) == buf_ret_size);
            if (wcsicmp(buf, L"C:\\Windows\\System32") == 0) {
                result = true;
            }
        }

        REQUIRE_FALSE(result);
        REQUIRE(FS_Search_Close(obj));
    }

    SECTION("system32-ok"){
        wchar_t buf[256]{};
        auto obj = FS_Search_QueryFolderW(L"System32", 3);
        REQUIRE(obj);

        auto count = FS_Search_GetCount(obj);
        REQUIRE(count > 0);

        bool result = false;
        for(size_t idx = 0; idx < count; idx++) {
            auto buf_ret_size = FS_Search_GetPathW(obj, idx, buf, std::size(buf));
            REQUIRE(wcslen(buf) == buf_ret_size);
            if (wcsicmp(buf, L"C:\\Windows\\System32") == 0) {
                result = true;
            }
        }

        REQUIRE(result);
        REQUIRE(FS_Search_Close(obj));
    }

    SECTION("system-regex"){
        wchar_t buf[256]{};
        auto obj = FS_Search_QueryFolderW(L"System(32)?", 3);
        REQUIRE(obj);

        auto count = FS_Search_GetCount(obj);
        REQUIRE(count > 1);

        bool result_s32 = false;
        bool result_s = false;

        for(size_t idx = 0; idx < count; idx++) {
            auto buf_ret_size = FS_Search_GetPathW(obj, idx, buf, std::size(buf));
            REQUIRE(wcslen(buf) == buf_ret_size);
            if (wcsicmp(buf, L"C:\\Windows\\System32") == 0) {
                result_s32 = true;
            }
            if (wcsicmp(buf, L"C:\\Windows\\System") == 0) {
                result_s = true;
            }
        }

        REQUIRE(result_s32);
        REQUIRE(result_s);

        REQUIRE(FS_Search_Close(obj));
    }
}