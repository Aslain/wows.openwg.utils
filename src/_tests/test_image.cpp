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

TEST_CASE( "image_resize", "[image]" ) {
    auto* h_bitmap = IMAGE_BitmapLoadW((std::filesystem::path(ASSETS_FOLDER)/L"splashscreen.png").wstring().c_str());
    REQUIRE(h_bitmap);

    int width = IMAGE_BitmapGetWidth(h_bitmap);
    int height = IMAGE_BitmapGetHeight(h_bitmap);
    REQUIRE(width > 0);
    REQUIRE(height > 0);

    SECTION("same_size")
    {
        auto* h_bitmap_2 = IMAGE_BitmapResize(h_bitmap, width, height);
        REQUIRE(h_bitmap_2);
        REQUIRE(IMAGE_BitmapFree(h_bitmap_2));
    }

    SECTION("scaling")
    {
        auto* h_bitmap_2 = IMAGE_BitmapResize(h_bitmap, width*2, height*2);
        REQUIRE(h_bitmap_2);
        REQUIRE(IMAGE_BitmapFree(h_bitmap_2));
    }

    REQUIRE(IMAGE_BitmapFree(h_bitmap));
}
