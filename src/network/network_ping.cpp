// SPDX-License-Identifier: MIT
// Copyright (c) 2023 OpenWG.Utils Contributors

//
// Includes
//

// stdlib
#include <vector>

// windows
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <icmpapi.h>
#include <windows.h>

// openwg
#include "network/network_ping.h"


namespace OpenWG::Utils::Network {
    int32_t Ping(uint32_t addr, int32_t timeout) {
        HANDLE handle_icmp{};

        handle_icmp = IcmpCreateFile();
        if (handle_icmp == INVALID_HANDLE_VALUE) {
            return -3;
        }

        std::vector<uint8_t> data_send(32);
        std::vector<uint8_t> data_reply(sizeof(ICMP_ECHO_REPLY) + data_send.size() + 8);

        auto result = IcmpSendEcho(handle_icmp, addr, data_send.data(), data_send.size(), nullptr, data_reply.data(),
                                   data_reply.size(), timeout);
        IcmpCloseHandle(handle_icmp);

        if (result != 1U) {
            return -4;
        }

        auto *reply = reinterpret_cast<PICMP_ECHO_REPLY>(data_reply.data());

        if (reply->Status == IP_DEST_HOST_UNREACHABLE || reply->Status == IP_DEST_NET_UNREACHABLE) {
            return -5;
        }
        if (reply->Status == IP_REQ_TIMED_OUT) {
            return -6;
        }

        return reply->RoundTripTime;
    }
}
