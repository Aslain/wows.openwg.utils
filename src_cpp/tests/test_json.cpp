// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

//
// Includes
//

#include <filesystem>

#include <catch2/catch_test_macros.hpp>

#include <json/api_json.h>



TEST_CASE( "json_open", "[json]" ) {
    SECTION("nullptr"){
        REQUIRE_FALSE(JSON_FileOpenW(nullptr, false));
        REQUIRE_FALSE(JSON_FileOpenW(nullptr, true));
    }

    SECTION("not_exists") {
        const wchar_t* filename = L"file_create_not_exists.json";
        if(std::filesystem::exists(filename)){
            std::filesystem::remove(filename);
        }
        REQUIRE_FALSE(JSON_FileOpenW(filename, false));
    }

    SECTION("allow_creation") {
        const wchar_t* filename = L"file_create_allow_creation.json";
        if(std::filesystem::exists(filename)){
            std::filesystem::remove(filename);
        }
        auto* ptr = JSON_FileOpenW(filename, true);
        REQUIRE(ptr != nullptr);
        REQUIRE(JSON_FileClose(ptr));
        REQUIRE(std::filesystem::exists(filename));
        std::filesystem::remove(filename);
    }
}

TEST_CASE( "json_set_bool", "[json]" ) {
    SECTION("nullptr") {
        REQUIRE_FALSE(JSON_SetBoolW(nullptr, L"meow", true));
        REQUIRE_FALSE(JSON_SetBoolW(reinterpret_cast<void*>(0x1234), nullptr, true));
    }

    SECTION("level_1") {
        const wchar_t* filename = L"set_bool_level_1.json";
        if(std::filesystem::exists(filename)){
            std::filesystem::remove(filename);
        }
        auto* ptr = JSON_FileOpenW(filename, true);
        REQUIRE(ptr != nullptr);

        REQUIRE_FALSE(JSON_SetBoolW(ptr, L"meow", true));

        REQUIRE(JSON_SetBoolW(ptr, L"/meow", true));
        REQUIRE(JSON_SetBoolW(ptr, L"/gaw", false));

        REQUIRE(JSON_FileClose(ptr));
        REQUIRE(std::filesystem::exists(filename));
        std::filesystem::remove(filename);
    }

    SECTION("level_2") {
        const wchar_t* filename = L"set_bool_level_2.json";
        if(std::filesystem::exists(filename)){
            std::filesystem::remove(filename);
        }
        auto* ptr = JSON_FileOpenW(filename, true);
        REQUIRE(ptr != nullptr);

        REQUIRE_FALSE(JSON_SetBoolW(ptr, L"meow/gaw", true));

        REQUIRE(JSON_SetBoolW(ptr, L"/meow/gaw", true));
        REQUIRE(JSON_SetBoolW(ptr, L"/meow/mur", true));
        REQUIRE(JSON_SetBoolW(ptr, L"/gaw", true));

        REQUIRE(JSON_FileClose(ptr));
        REQUIRE(std::filesystem::exists(filename));
        std::filesystem::remove(filename);
    }
}

