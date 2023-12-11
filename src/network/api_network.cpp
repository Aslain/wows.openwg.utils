// SPDX-License-Identifier: MIT
// Copyright (c) 2023 OpenWG.Utils Contributors

#include "network/api_network.h"
#include "network/network_ping.h"
#include "network/network_resolve.h"


using namespace OpenWG::Utils;

int32_t NETWORK_PingW(_In_ const wchar_t* hostname, _In_ int32_t timeout) {
    if (!hostname) {
        return -1;
    }

    auto ipv4_addr = Network::Resolve(hostname);
    if (!ipv4_addr) {
        return -2;
    }

    return Network::Ping(ipv4_addr, timeout);
}


uint32_t NETWORK_ResolveW(_In_ const wchar_t* hostname){
    if(!hostname){
        return 0U;
    }
    return Network::Resolve(hostname);
}
