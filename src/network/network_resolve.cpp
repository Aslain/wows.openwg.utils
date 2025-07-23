// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

//
// Includes
//

// windows
#if defined(_WIN32)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#endif

// openwg
#include "network/network_ping.h"


namespace OpenWG::Utils::Network {
    uint32_t Resolve(const std::wstring &host) {
#if defined(_WIN32)
        if (host.empty()) {
            return 0U;
        }

        WSADATA wsa_data{};
        WSAStartup(MAKEWORD(2, 2), &wsa_data);

        ADDRINFOW addr_hints{};
        ADDRINFOW *addr_result{};
        addr_hints.ai_socktype = SOCK_STREAM;
        addr_hints.ai_family = AF_INET;

        if (GetAddrInfoW(host.c_str(), nullptr, &addr_hints, &addr_result) != NO_ERROR) {
            return 0U;
        }

        auto ipaddr = ((struct sockaddr_in *) (addr_result->ai_addr))->sin_addr.S_un.S_addr;

        FreeAddrInfoW(addr_result);
        WSACleanup();

        return ipaddr;
#else
        return {};
#endif
    }
}
