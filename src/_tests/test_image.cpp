// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

//
// Includes
//

#include <filesystem>
#include <fstream>

#include <catch2/catch_test_macros.hpp>

#include <image/api_image.h>



//
// Tests
//

TEST_CASE( "image_load_file", "[image]" ) {
    auto* h_bitmap = IMAGE_BitmapLoadW((std::filesystem::path(ASSETS_FOLDER)/L"splashscreen.png").wstring().c_str());
    REQUIRE(h_bitmap);

    REQUIRE(IMAGE_BitmapAlphaPremultiply(h_bitmap));
    REQUIRE(IMAGE_BitmapFree(h_bitmap));
}
