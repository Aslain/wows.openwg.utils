// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#include <string>
#include <vector>
#include "wotclient.h"

class WotDetector {
private:
    static bool isInitialized;
public:
    static std::vector<WotClient> clients;

    static void FindClients();
    static int AddClient(std::wstring directory,WgcFlavour flavour = WgcFlavour::Unknown);
    static bool IsInitialized();
};
