// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

//
// Includes
//

#include <filesystem>
#include <catch2/catch_test_macros.hpp>
#include "xml/api_xml.h"



//
// Test
//


TEST_CASE( "xml_openfile", "[xml]" ) {
    SECTION("nullptr") {
        REQUIRE_FALSE(XML_OpenFileW(nullptr, false));
        REQUIRE_FALSE(XML_OpenFileW(nullptr, true));
    }

    SECTION("not_existing") {
        REQUIRE_FALSE(
                XML_OpenFileW((std::filesystem::path(ASSETS_FOLDER) / "xml_adobe_not1.xml").wstring().c_str(), false));
        REQUIRE(XML_OpenFileW((std::filesystem::path(ASSETS_FOLDER) / "xml_adobe_not2.xml").wstring().c_str(), true));
    }

    SECTION("existing") {
        REQUIRE(XML_OpenFileW((std::filesystem::path(ASSETS_FOLDER) / "xml_adobe.xml").wstring().c_str(), false));
        REQUIRE(XML_OpenFileW((std::filesystem::path(ASSETS_FOLDER) / "xml_adobe.xml").wstring().c_str(), true));
    }
}


TEST_CASE( "xml_containskey", "[xml]" ) {
    SECTION("nullptr") {
        REQUIRE_FALSE(XML_ContainsKeyW(nullptr, nullptr));
        REQUIRE_FALSE(XML_ContainsKeyW(nullptr, L"/meow"));
        REQUIRE_FALSE(XML_ContainsKeyW((void *) 0x1234567, nullptr));
    }

    SECTION("contains") {
        void *obj = XML_OpenFileW((std::filesystem::path(ASSETS_FOLDER) / "xml_adobe.xml").wstring().c_str(), false);
        REQUIRE(obj != nullptr);
        REQUIRE(XML_ContainsKeyW(obj, L"/plist/dict[1]/dict/array[3]/string"));
        REQUIRE_FALSE(XML_ContainsKeyW(obj, L"/plist/dict[1]/dict/array[1233]/string"));
        REQUIRE(XML_Close(obj));
    }
}


TEST_CASE( "xml_containskey_ex", "[xml]" ) {
    SECTION("nullptr") {
        REQUIRE_FALSE(XML_ContainsKeyExW(nullptr, nullptr, nullptr));
        REQUIRE_FALSE(XML_ContainsKeyExW(nullptr, L"/meow", nullptr));
        REQUIRE_FALSE(XML_ContainsKeyExW((void *) 0x1234567, nullptr, nullptr));
        REQUIRE_FALSE(XML_ContainsKeyExW((void *) 0x1234567, L"/meow", nullptr));
    }

    SECTION("contains") {
        void *obj = XML_OpenFileW((std::filesystem::path(ASSETS_FOLDER) / "xml_adobe.xml").wstring().c_str(), false);
        REQUIRE(obj != nullptr);
        REQUIRE(XML_ContainsKeyExW(obj, L"/plist/dict[1]/dict[3]/array[3]/string", L"en_US"));
        REQUIRE_FALSE(XML_ContainsKeyExW(obj, L"/plist/dict[1]/dict/array[1233]/string", L"lol_KEK"));
        REQUIRE(XML_Close(obj));
    }
}


TEST_CASE( "xml_addkey_ex", "[xml]" ) {
    SECTION("nullptr") {
        REQUIRE_FALSE(XML_AddKeyW(nullptr, nullptr, nullptr, nullptr));
        REQUIRE_FALSE(XML_AddKeyW(nullptr, L"ll", L"oo", L"lll"));
        REQUIRE_FALSE(XML_AddKeyW((void *) 0x1234567, nullptr, L"oo", L"lll"));
        REQUIRE_FALSE(XML_AddKeyW((void *) 0x1234567, L"l", nullptr, L"lll"));
        REQUIRE_FALSE(XML_AddKeyW((void *) 0x1234567, L"l", L"oo", nullptr));
    }

    SECTION("correct") {
        void *obj = XML_OpenFileW((std::filesystem::path(ASSETS_FOLDER) / "xml_adobe.xml").wstring().c_str(), false);
        REQUIRE(obj != nullptr);
        REQUIRE_FALSE(XML_AddKeyW(obj, L"/plist/dict[1]/dict[3]/array[1]/string", L"string", L"be_BY"));
        REQUIRE(XML_AddKeyW(obj, L"/plist/dict[1]/dict[3]/array[1]", L"string", L"be_BY"));
        REQUIRE_FALSE(XML_AddKeyW(obj, L"/plist/dict[1]/dict[3]/array[3]/string", L"string", L"be_BY"));
        REQUIRE(XML_AddKeyW(obj, L"/plist/dict[1]/dict[3]/array[3]", L"string", L"be_BY"));
        REQUIRE(XML_SaveFileW(obj,  (std::filesystem::path(ASSETS_FOLDER) / "xml_adobe_2.xml").wstring().c_str()));
        REQUIRE(XML_Close(obj));
    }
}