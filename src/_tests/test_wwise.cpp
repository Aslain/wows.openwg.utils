// SPDX-License-Identifier: MIT
// Copyright (c) 2023 OpenWG.Utils Contributors

//
// Includes
//

// stdlib
#include <filesystem>

// catch2
#include <catch2/catch_test_macros.hpp>

// openwg.utils
#include "common/api_common.h"
#include "fs/api_fs.h"
#include "wwise/api_wwise.h"



//
// Tests
//

TEST_CASE("wwise_openclose"){
    SECTION("null"){
        REQUIRE_FALSE(WWISE_OpenFileW(nullptr));
        REQUIRE_FALSE(WWISE_Close(nullptr));
    }

    SECTION("not exists"){
        REQUIRE_FALSE(WWISE_OpenFileW(L"not-existing-file.bnk"));
    }

    SECTION("existing file"){
        auto ptr = WWISE_OpenFileW(std::filesystem::path(std::filesystem::path(ASSETS_FOLDER) / "soundbank_license_no.bnk").wstring().c_str());
        REQUIRE(ptr != nullptr);
        REQUIRE(WWISE_Close(ptr));
    }
}

TEST_CASE("wwise_license_get"){
    SECTION("not exists"){
        REQUIRE(WWISE_LicenseGet(nullptr) == WwiseLicense_Unknown);
    }

    SECTION("existing/no_license"){
        auto ptr = WWISE_OpenFileW(std::filesystem::path(std::filesystem::path(ASSETS_FOLDER) / "soundbank_license_no.bnk").wstring().c_str());
        REQUIRE(WWISE_LicenseGet(ptr) == WwiseLicense_Unlicensed);
        REQUIRE(WWISE_LicenseGet(ptr) == WwiseLicense_Unlicensed);
        REQUIRE(WWISE_Close(ptr));
    }
    SECTION("existing/no_license_2"){
        auto ptr = WWISE_OpenFileW(std::filesystem::path(std::filesystem::path(ASSETS_FOLDER) / "voiceover_lesta.bnk").wstring().c_str());
        REQUIRE(WWISE_LicenseGet(ptr) == WwiseLicense_Unlicensed);
        REQUIRE(WWISE_LicenseGet(ptr) == WwiseLicense_Unlicensed);
        REQUIRE(WWISE_Close(ptr));
    }

    SECTION("existing/wg"){
        auto ptr = WWISE_OpenFileW(std::filesystem::path(std::filesystem::path(ASSETS_FOLDER) / "soundbank_license_wg.bnk").wstring().c_str());
        REQUIRE(WWISE_LicenseGet(ptr) == WwiseLicense_Wargaming);
        REQUIRE(WWISE_LicenseGet(ptr) == WwiseLicense_Wargaming);
        REQUIRE(WWISE_Close(ptr));
    }
    SECTION("existing/wg_2"){
        auto ptr = WWISE_OpenFileW(std::filesystem::path(std::filesystem::path(ASSETS_FOLDER) / "voiceover_wg.bnk").wstring().c_str());
        REQUIRE(WWISE_LicenseGet(ptr) == WwiseLicense_Wargaming);
        REQUIRE(WWISE_LicenseGet(ptr) == WwiseLicense_Wargaming);
        REQUIRE(WWISE_Close(ptr));
    }
}

TEST_CASE("wwise_license_set"){
    SECTION("not exists") {
        REQUIRE_FALSE(WWISE_LicenseSet(nullptr, 1));
    }

    SECTION("exists"){
        auto ptr = WWISE_OpenFileW(std::filesystem::path(std::filesystem::path(ASSETS_FOLDER) / "soundbank_license_wg.bnk").wstring().c_str());
        REQUIRE(WWISE_LicenseGet(ptr) == WwiseLicense_Wargaming);
        REQUIRE(WWISE_LicenseSet(ptr, WwiseLicense_Unlicensed));
        REQUIRE(WWISE_LicenseGet(ptr) == WwiseLicense_Unlicensed);
        REQUIRE(WWISE_SaveFileW(ptr,std::filesystem::path(std::filesystem::path(ASSETS_FOLDER) / "soundbank_license_wg_2.bnk").wstring().c_str()));
        REQUIRE(WWISE_Close(ptr));

        auto ptr_2 = WWISE_OpenFileW(std::filesystem::path(std::filesystem::path(ASSETS_FOLDER) / "soundbank_license_wg_2.bnk").wstring().c_str());
        REQUIRE(WWISE_LicenseGet(ptr_2) == WwiseLicense_Unlicensed);
        REQUIRE(WWISE_Close(ptr_2));

        std::filesystem::remove(std::filesystem::path(ASSETS_FOLDER) / "soundbank_license_wg_2.bnk");
    }

    SECTION("lesta_license") {
        SECTION("wg->none")
        {
            auto ptr_wg = WWISE_OpenFileW(std::filesystem::path(
                    std::filesystem::path(ASSETS_FOLDER) / "u_wg.bnk").wstring().c_str());
            REQUIRE(ptr_wg != nullptr);
            REQUIRE(WWISE_LicenseGet(ptr_wg) == WwiseLicense_Wargaming);
            REQUIRE(WWISE_LicenseSet(ptr_wg, WwiseLicense_Unlicensed));
            REQUIRE(WWISE_BKHD_ProjectId_Set(ptr_wg, 0x0000));
            REQUIRE(WWISE_SaveFileW(ptr_wg, std::filesystem::path(
                    std::filesystem::path(ASSETS_FOLDER) / "u_wg_2.bnk").wstring().c_str()));

            auto res = FS_File_IsEqualW(
                    (std::filesystem::path(ASSETS_FOLDER) / "u_wg_2.bnk").wstring().c_str(),
                    (std::filesystem::path(ASSETS_FOLDER) / "u_none.bnk").wstring().c_str()
                    );

            std::filesystem::remove(std::filesystem::path(ASSETS_FOLDER) / "u_wg_2.bnk");
            REQUIRE(res);
        }
    }
}
