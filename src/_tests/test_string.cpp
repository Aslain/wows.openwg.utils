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

        output.resize(-result);
        result =  STRING_ReplaceRegex(input.c_str(), pattern.c_str(), replacement.c_str(), output.data(), output.size()+1);
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
            output.resize(input.size() * 2);

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
        int result = STRING_ReplaceRegex(input.c_str(), pattern.c_str(), replacement.c_str(), output.data(), output.size() + 1);
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