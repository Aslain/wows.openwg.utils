// SPDX-License-Identifier: MIT
// Copyright (c) 2023 OpenWG.Utils Contributors

//
// Includes
//

#include <catch2/catch_test_macros.hpp>

#include <wwise/api_wwise.h>
#include <wwise/wwise_bank.h>
#include <wwise/wwise_utils.h>

using namespace OpenWG::Utils::WWISE;

//
// WWISE_TEST
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
}

TEST_CASE( "wwise_bkhd", "[wwise]" ) {
    SECTION("nolicense_empty"){
        Bank bnk{};
        bnk.Read(std::filesystem::path(std::filesystem::path(ASSETS_FOLDER) / "soundbank_license_no.bnk"));

        auto& bkhd = bnk.BKHD();
        REQUIRE(bkhd.GetVersion() == 0x87);
        REQUIRE(bkhd.GetAlignment() == 16);
        REQUIRE(bkhd.GetDeviceAllocated() == 0);
        REQUIRE(bkhd.GetProjectId() == 0);

        {
            FNVHash32 hash{};
            hash.Compute("new_soundbank", strlen("new_soundbank"));
            REQUIRE(bkhd.GetBankId() == hash.Get());
        }

        {
            REQUIRE(bkhd.GetLanguageId() == 0x17705d3e);
        }
    }

    SECTION("wg_empty") {
        Bank bnk{};
        bnk.Read(std::filesystem::path(std::filesystem::path(ASSETS_FOLDER) / "soundbank_license_wg.bnk"));


        auto& bkhd = bnk.BKHD();

        License lic{};
        lic.m_key[0] = 0xD2F5B297;
        lic.m_key[1] = 0xC57DA87E;
        lic.m_key[2] = 0xD10C0503;
        lic.m_key[3] = 0x6B0403D4;

        REQUIRE(bkhd.Decrypt(lic));

        REQUIRE(bkhd.GetVersion() == 0x87);
        REQUIRE(bkhd.GetAlignment() == 16);
        REQUIRE(bkhd.GetDeviceAllocated() == 0);
        REQUIRE(bkhd.GetProjectId() == 0x0F2E);

        {
            FNVHash32 hash{};
            hash.Compute("new_soundbank", strlen("new_soundbank"));
            REQUIRE(bkhd.GetBankId() == hash.Get());
        }

        {
            REQUIRE(bkhd.GetLanguageId() == 0x17705d3e);
        }
    }

    SECTION("wg_voiceover") {
        Bank bnk{};
        bnk.Read(std::filesystem::path(std::filesystem::path(ASSETS_FOLDER) / "voiceover_wg.bnk"));

        auto& bkhd = bnk.BKHD();

        License lic{};
        lic.m_key[0] = 0xD2F5B297;
        lic.m_key[1] = 0xC57DA87E;
        lic.m_key[2] = 0xD10C0503;
        lic.m_key[3] = 0x6B0403D4;

        REQUIRE(bkhd.Decrypt(lic));

        REQUIRE(bkhd.GetVersion() == 0x87);
        REQUIRE(bkhd.GetAlignment() == 16);
        REQUIRE(bkhd.GetDeviceAllocated() == 0);
        REQUIRE(bkhd.GetProjectId() == 0x05AD);

        {
            FNVHash32 hash{};
            hash.Compute("voiceover", strlen("voiceover"));
            REQUIRE(bkhd.GetBankId() == hash.Get());
        }

        {
            REQUIRE(bkhd.GetLanguageId() == 0x65fde48a);
        }
    }

    SECTION("lesta_voiceover") {
        Bank bnk{};
        bnk.Read(std::filesystem::path(std::filesystem::path(ASSETS_FOLDER) / "voiceover_lesta.bnk"));

        auto& bkhd = bnk.BKHD();

        REQUIRE(bkhd.GetVersion() == 0x87);
        REQUIRE(bkhd.GetAlignment() == 16);
        REQUIRE(bkhd.GetDeviceAllocated() == 0);
        REQUIRE(bkhd.GetProjectId() == 0x3741);

        {
            FNVHash32 hash{};
            hash.Compute("voiceover", strlen("voiceover"));
            REQUIRE(bkhd.GetBankId() == hash.Get());
        }

        {
            REQUIRE(bkhd.GetLanguageId() == 0x686a6d9c);
        }
    }
}