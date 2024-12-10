// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

//
// Includes
//

#include <catch2/catch_test_macros.hpp>

#include <network/api_network.h>


//
// STRING_ReplaceRegex
//

TEST_CASE( "network_resolve", "[network]" ) {
    SECTION("nullptr"){
        REQUIRE_FALSE(NETWORK_ResolveW(nullptr));
        REQUIRE_FALSE(NETWORK_ResolveW(L""));
        REQUIRE_FALSE(NETWORK_ResolveW(L"2001:db8:3333:4444:5555:6666:7777:8888"));
        REQUIRE_FALSE(NETWORK_ResolveW(L"not-existing-domain"));

    }

    SECTION("ok"){
        REQUIRE(NETWORK_ResolveW(L"1.1.1.1") == 0x01010101);
        REQUIRE(NETWORK_ResolveW(L"8.8.8.8") == 0x08080808);
    }
}

TEST_CASE( "network_ping", "[network]" ) {
    SECTION("nullptr"){
        REQUIRE(NETWORK_PingW(nullptr, 1000) < 0);
        REQUIRE(NETWORK_PingW(L"not-existing-domain", 1000) < 0);
    }

    SECTION("ok") {
        REQUIRE(NETWORK_PingW(L"1.1.1.1", 1000) >= 0);
    }
}