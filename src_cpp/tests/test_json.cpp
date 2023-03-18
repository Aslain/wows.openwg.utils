// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

//
// Includes
//

#include <filesystem>
#include <fstream>

#include <catch2/catch_test_macros.hpp>

#include <json/api_json.h>



TEST_CASE( "json_open", "[json]" ) {
    SECTION("nullptr"){
        REQUIRE_FALSE(JSON_OpenFileW(nullptr, false));
        REQUIRE_FALSE(JSON_OpenFileW(nullptr, true));
    }

    SECTION("not_exists") {
        const wchar_t* filename = L"file_create_not_exists.json";
        if(std::filesystem::exists(filename)){
            std::filesystem::remove(filename);
        }
        REQUIRE_FALSE(JSON_OpenFileW(filename, false));
    }

    SECTION("allow_creation") {
        const wchar_t* filename = L"file_create_allow_creation.json";
        if(std::filesystem::exists(filename)){
            std::filesystem::remove(filename);
        }
        auto* ptr = JSON_OpenFileW(filename, true);
        REQUIRE(ptr != nullptr);
        REQUIRE(JSON_Close(ptr));
        REQUIRE(std::filesystem::exists(filename));
    }

    SECTION("comments"){
        const wchar_t* filename = L"file_open_comments.json";
        const char* infile =
        "{ \n"
        "    //auto_update              \n"
        "	 \"auto_update\"    : false,\n"
        "    // player_profile          \n"
        "	 \"player_profile\" : false \n"
        "}";
        std::ofstream f(filename);
        f << infile;
        f.close();

        REQUIRE(std::filesystem::exists(filename));

        auto* ptr = JSON_OpenFileW(filename, true);
        REQUIRE(ptr != nullptr);

        REQUIRE(JSON_SetBoolW(ptr,L"/player_profile",false));
        REQUIRE(JSON_SetBoolW(ptr,L"/auto_update", true));
        REQUIRE(JSON_SetIntegerW(ptr,L"/new_stuff", 123));
        REQUIRE(JSON_Close(ptr));

        REQUIRE(std::filesystem::exists(filename));

        std::ifstream t(filename);
        std::string str((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
        f.close();

        REQUIRE(str.contains("//"));

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
        auto* ptr = JSON_OpenFileW(filename, true);
        REQUIRE(ptr != nullptr);

        REQUIRE_FALSE(JSON_SetBoolW(ptr, L"meow", true));

        REQUIRE(JSON_SetBoolW(ptr, L"/meow", true));
        REQUIRE(JSON_SetBoolW(ptr, L"/gaw", false));

        REQUIRE(JSON_Close(ptr));
        REQUIRE(std::filesystem::exists(filename));
    }

    SECTION("level_2") {
        const wchar_t* filename = L"set_bool_level_2.json";
        if(std::filesystem::exists(filename)){
            std::filesystem::remove(filename);
        }
        auto* ptr = JSON_OpenFileW(filename, true);
        REQUIRE(ptr != nullptr);

        REQUIRE_FALSE(JSON_SetBoolW(ptr, L"meow/gaw", true));

        REQUIRE(JSON_SetBoolW(ptr, L"/meow/gaw", true));
        REQUIRE(JSON_SetBoolW(ptr, L"/meow/mur", true));
        REQUIRE(JSON_SetBoolW(ptr, L"/kukareku", true));

        REQUIRE(JSON_Close(ptr));
        REQUIRE(std::filesystem::exists(filename));
    }
}


TEST_CASE( "json_set_double", "[json]" ) {
    SECTION("nullptr") {
        REQUIRE_FALSE(JSON_SetDoubleW(nullptr, L"meow", 1.2));
        REQUIRE_FALSE(JSON_SetDoubleW(reinterpret_cast<void*>(0x1234), nullptr, 1.2));
    }

    SECTION("level_1") {
        const wchar_t* filename = L"set_double_level_1.json";
        if(std::filesystem::exists(filename)){
            std::filesystem::remove(filename);
        }
        auto* ptr = JSON_OpenFileW(filename, true);
        REQUIRE(ptr != nullptr);

        REQUIRE_FALSE(JSON_SetDoubleW(ptr, L"gaw", 1.1));
        REQUIRE_FALSE(JSON_SetDoubleW(ptr, L"gaw/", 1.2));
        REQUIRE_FALSE(JSON_SetDoubleW(ptr, L"/gaw/", 1.3));

        REQUIRE(JSON_SetDoubleW(ptr, L"/gaw", 1.3));
        REQUIRE(JSON_SetDoubleW(ptr, L"/meow", 1.5));

        REQUIRE(JSON_Close(ptr));
        REQUIRE(std::filesystem::exists(filename));
    }
}


TEST_CASE( "json_set_integer", "[json]" ) {
    SECTION("nullptr") {
        REQUIRE_FALSE(JSON_SetIntegerW(nullptr, L"meow", 1));
        REQUIRE_FALSE(JSON_SetIntegerW(reinterpret_cast<void*>(0x1234), nullptr, 1));
    }

    SECTION("level_1") {
        const wchar_t* filename = L"set_integer_level_1.json";
        if(std::filesystem::exists(filename)){
            std::filesystem::remove(filename);
        }
        auto* ptr = JSON_OpenFileW(filename, true);
        REQUIRE(ptr != nullptr);

        REQUIRE_FALSE(JSON_SetIntegerW(ptr, L"gaw", 1));
        REQUIRE_FALSE(JSON_SetIntegerW(ptr, L"gaw/", 1));
        REQUIRE_FALSE(JSON_SetIntegerW(ptr, L"/gaw/", 1));

        REQUIRE(JSON_SetIntegerW(ptr, L"/gaw", 1));
        REQUIRE(JSON_SetIntegerW(ptr, L"/meow", 2));

        REQUIRE(JSON_Close(ptr));
        REQUIRE(std::filesystem::exists(filename));
    }
}


TEST_CASE( "json_set_string", "[json]" ) {
    SECTION("nullptr") {
        REQUIRE_FALSE(JSON_SetStringW(nullptr, L"meow", L"gaw"));
        REQUIRE_FALSE(JSON_SetStringW(reinterpret_cast<void *>(0x1234), nullptr, L"gaw"));
        REQUIRE_FALSE(JSON_SetStringW(reinterpret_cast<void *>(0x1234), L"meow", nullptr));
    }

    SECTION("level_3") {
        const wchar_t* filename = L"set_string_level_3.json";
        if(std::filesystem::exists(filename)){
            std::filesystem::remove(filename);
        }
        auto* ptr = JSON_OpenFileW(filename, true);
        REQUIRE(ptr != nullptr);

        REQUIRE_FALSE(JSON_SetStringW(ptr, L"meow/gaw", L"one"));
        REQUIRE_FALSE(JSON_SetStringW(ptr, L"/meow/gaw", nullptr));

        REQUIRE(JSON_SetStringW(ptr, L"/meow/gaw", L"two"));
        REQUIRE(JSON_SetStringW(ptr, L"/kukareku", L"two"));
        REQUIRE(JSON_SetStringW(ptr, L"/kek/lol/azaza", L"three"));

        REQUIRE(JSON_Close(ptr));
        REQUIRE(std::filesystem::exists(filename));
    }
}