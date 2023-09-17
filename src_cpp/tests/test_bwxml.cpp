// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

//
// Includes
//

#include <filesystem>
#include <catch2/catch_test_macros.hpp>
#include "bwxml/api_bwxml.h"



//
// Test
//

TEST_CASE( "bwxml_unpack", "[bwxml]" ) {
    SECTION("nullptr") {
        REQUIRE(BWXML_UnpackW(nullptr, nullptr)     < 0);
        REQUIRE(BWXML_UnpackW(L"C:\1.xml", nullptr) < 0);
        REQUIRE(BWXML_UnpackW(nullptr, L"C:\1.xml") < 0);
    }

    SECTION("unpack") {
        REQUIRE(BWXML_UnpackW((std::filesystem::path(ASSETS_FOLDER) / "engine_config.xml").wstring().c_str(), L"engine_config.xml") == 0);
    }
}
