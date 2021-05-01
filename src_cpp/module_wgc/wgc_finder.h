#pragma once

#include <vector>
#include <string>
#include <utility>

#include "wgc_flavour.h"
#include "wgc_client.h"

class WgcFinder {
public:
    WgcFinder() = delete;
    ~WgcFinder() = delete;

    static std::vector<WgcClient> GetWgcClients();

private:
    static std::vector<std::pair<std::wstring, WgcFlavour>> _programdata_suffixes;
};
