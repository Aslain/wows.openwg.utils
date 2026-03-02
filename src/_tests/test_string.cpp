// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

//
// Includes
//

// stdlib
#include <fstream>
#include <filesystem>
#include <string>

// catch2
#include <catch2/catch_test_macros.hpp>

// openwg.utils
#include <string/api_string.h>

#include "fs/api_fs.h"


//
// STRING_LoadFromFile
//

TEST_CASE("string_load_from_file", "[string]") {
    SECTION("non-existent") {
        auto filepath = std::filesystem::path(ROOT_FOLDER) / "string" / "test_assets" / "does_not_exists.txt";
        std::vector<wchar_t> bytes;
        bytes.resize(1);
        auto result = STRING_LoadFromFile(filepath.wstring().c_str(), bytes.data(), bytes.size()*sizeof(wchar_t));
        REQUIRE(result == INT_MIN);
    }

    SECTION("small-buf") {
        auto filepath = std::filesystem::path(ROOT_FOLDER) / "string" / "test_assets" / "string_load_from_file_1_utf8.txt";
        std::vector<wchar_t> bytes;
        bytes.resize(10);
        auto result = STRING_LoadFromFile(filepath.wstring().c_str(), bytes.data(), bytes.size()*sizeof(wchar_t));
        REQUIRE(result == -160);
    }

    SECTION("ok-utf8") {
        auto filepath = std::filesystem::path(ROOT_FOLDER) / "string" / "test_assets" / "string_load_from_file_1_utf8.txt";
        std::vector<wchar_t> bytes;
        bytes.resize(160);
        auto result = STRING_LoadFromFile(filepath.wstring().c_str(), bytes.data(), bytes.size()*sizeof(wchar_t));
        REQUIRE(result == 160);
    }

    SECTION("ok-utf8-bom") {
        auto filepath = std::filesystem::path(ROOT_FOLDER) / "string" / "test_assets" / "string_load_from_file_1_utf8bom.txt";
        std::vector<wchar_t> bytes;
        bytes.resize(166);
        auto result = STRING_LoadFromFile(filepath.wstring().c_str(), bytes.data(), bytes.size()*sizeof(wchar_t));
        REQUIRE(result == 160);
    }

    SECTION("ok-utf16") {
        auto filepath = std::filesystem::path(ROOT_FOLDER) / "string" / "test_assets" / "string_load_from_file_1_utf16le.txt";
        std::vector<wchar_t> bytes;
        bytes.resize(316);
        auto result = STRING_LoadFromFile(filepath.wstring().c_str(), bytes.data(), bytes.size()*sizeof(wchar_t));
        REQUIRE(result == 158);
    }
}



//
// STRING_MatchRegex
//

TEST_CASE("string_match_regex", "[string]") {
    SECTION("nullptr") {
        const wchar_t* str = L"";
        REQUIRE(STRING_MatchRegex(nullptr, nullptr) == 0);
        REQUIRE(STRING_MatchRegex(str, nullptr) == 0);
        REQUIRE(STRING_MatchRegex(nullptr, str) == 0);
    }

    SECTION("cyr") {
        const wchar_t* str_1 = L"abcdef";
        const wchar_t* str_2 = L"абвгдеsda";
        const wchar_t* str_3 = L"ІЎіў";
        const wchar_t* patt = L"[\x0400-\x04FF\x0500-\x052F\xA640-\xA69F\x1C80-\x1C8F]";
        REQUIRE_FALSE(STRING_MatchRegex(str_1, patt));
        REQUIRE(STRING_MatchRegex(str_2, patt));
        REQUIRE(STRING_MatchRegex(str_3, patt));
    }
}



//
// STRING_ReplaceRegex
//

TEST_CASE( "string_replace_regex", "[string]" ) {
    SECTION("nullptr"){
        const wchar_t* str = L"";
        REQUIRE(STRING_ReplaceRegex(nullptr, nullptr, nullptr, nullptr, 1) == 0);
        REQUIRE(STRING_ReplaceRegex(str, nullptr, nullptr, nullptr, 1) == 0);
        REQUIRE(STRING_ReplaceRegex(nullptr, str, nullptr, nullptr, 1) == 0);
        REQUIRE(STRING_ReplaceRegex(nullptr, nullptr, str, nullptr, 1) == 0);
    }

    SECTION("too_small"){
        std::wstring input{L"gaw-gaw-gaw"};
        std::wstring pattern{L"gaw"};
        std::wstring replacement{L"meow"};
        std::wstring output;
        output.resize(input.size());

        int result =  STRING_ReplaceRegex(input.c_str(), pattern.c_str(), replacement.c_str(), output.data(), output.size()+1);
        REQUIRE(result < 0);

        output.resize(-(result+1)/2);
        result =  STRING_ReplaceRegex(input.c_str(), pattern.c_str(), replacement.c_str(), output.data(), (output.size()+1)*sizeof(wchar_t));
        REQUIRE(result > 0);
        REQUIRE(output.size() == wcslen(output.data()));
        REQUIRE(output == L"meow-meow-meow");
    }

    SECTION("pattern"){
        std::wstring input{L"meow moo gaw"};
        std::wstring pattern{L"((meow).*?(gaw))"};

        SECTION("replacement_1") {
            std::wstring replacement{L"$1"};
            std::wstring output;
            output.resize((input.size()+1) * 2);

            int result = STRING_ReplaceRegex(input.c_str(), pattern.c_str(), replacement.c_str(), output.data(),
                                             output.size() + 1);
            REQUIRE(result > 0);
            output.resize(wcslen(output.data()));
            REQUIRE(output == L"meow moo gaw");
        }

        SECTION("replacement_2") {
            std::wstring replacement{L"$2"};
            std::wstring output;
            output.resize(input.size() * 2);

            int result = STRING_ReplaceRegex(input.c_str(), pattern.c_str(), replacement.c_str(), output.data(),
                                             output.size() + 1);
            REQUIRE(result > 0);
            output.resize(wcslen(output.data()));
            REQUIRE(output == L"meow");
        }

        SECTION("replacement_3") {
            std::wstring replacement{L"$3"};
            std::wstring output;
            output.resize(input.size() * 2);

            int result = STRING_ReplaceRegex(input.c_str(), pattern.c_str(), replacement.c_str(), output.data(),
                                             output.size() + 1);
            REQUIRE(result > 0);
            output.resize(wcslen(output.data()));
            REQUIRE(output == L"gaw");
        }
    }
}


TEST_CASE( "string_replace_regex_sk", "[string]" ) {
    SECTION("tg_1470694134_148287"){
        std::wstring input{L"\n{\n  \"enable\": false\n}"};
        std::wstring pattern{L"((\\n|\\r|\\r\\n){(.|\\s)+?\"enable\"\\s*:\\s*)(true|false)"};
        std::wstring replacement{L"$1true"};
        std::wstring output{};
        output.resize(input.size());
        int result = STRING_ReplaceRegex(input.c_str(), pattern.c_str(), replacement.c_str(), output.data(), (output.size() + 1)*sizeof(wchar_t));
        REQUIRE(result > 0);
        output.resize(wcslen(output.data()));
        REQUIRE(output == L"\n{\n  \"enable\": true\n}");
    }
}


TEST_CASE("string_replace_regex_ex_jove_1", "[string]") {
    std::wstring before;
    std::wstring after_expected;
    {
        std::ifstream fin(std::filesystem::path(ASSETS_FOLDER) / "string_replace_1_before.txt", std::ios::binary);
        fin.seekg(0, std::ios::end);
        size_t size = (size_t)fin.tellg();
        //skip BOM

        fin.seekg(2, std::ios::beg);
        size -= 2;

        before.resize(size / 2 + 1);
        fin.read((char*)before.data(), size);
    }
    {
        std::ifstream fin(std::filesystem::path(ASSETS_FOLDER) / "string_replace_1_after.txt", std::ios::binary);
        fin.seekg(0, std::ios::end);
        size_t size = (size_t)fin.tellg();
        //skip BOM

        fin.seekg(2, std::ios::beg);
        size -= 2;

        after_expected.resize(size / 2);
        fin.read((char*)after_expected.data(), size);
    }

    std::wstring output{};
    output.resize(before.size()*2);
    auto result = STRING_ReplaceRegexEx(before.c_str(), 
        L"(\"enable\"\\s*:\\s*)(true|false)(.*)",
        L"$1true$3", 
        output.data(),
        output.size(),
        true
    );
    REQUIRE(result > 0);
    output.resize(wcslen(output.data()));
    REQUIRE(output == after_expected);
}

TEST_CASE("string_replace_regex_1", "[string]") {
    auto filename = std::filesystem::path(ROOT_FOLDER) / "string" / "test_assets" / "string_replace_regex_1_before.txt";
    REQUIRE(FS_FileExistsW(filename.wstring().c_str()));
    REQUIRE(FS_FileSizeW(filename.wstring().c_str()) == 80);

    std::wstring str_before;
    // 80 UTF-16 chars payload + null terminator
    str_before.resize(81);
    REQUIRE(STRING_LoadFromFile(filename.wstring().c_str(), str_before.data(), str_before.size()*sizeof(wchar_t)) == 160);

    std::wstring str_after;
    auto size_after =  STRING_ReplaceRegex(str_before.c_str(),
        L"(<loadBanks>)",
        L"$1<bank><name>extended_sounds.bnk</name></bank><bank><name>hangar_h04_remday_2015.bnk</name></bank>", str_after.data(), str_after.size()*sizeof(wchar_t));
    REQUIRE(size_after == -356);

    str_after.resize(356/sizeof(wchar_t));
    size_after =  STRING_ReplaceRegex(str_before.c_str(),
          L"(<loadBanks>)",
          L"$1<bank><name>extended_sounds.bnk</name></bank><bank><name>hangar_h04_remday_2015.bnk</name></bank>", str_after.data(), str_after.size()*sizeof(wchar_t));
    REQUIRE(size_after == 356);

}
