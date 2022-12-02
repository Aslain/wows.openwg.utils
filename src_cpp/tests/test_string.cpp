// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

//
// Includes
//

#include <catch2/catch_test_macros.hpp>

#include <string/api_string.h>


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