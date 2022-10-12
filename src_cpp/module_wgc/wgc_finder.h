#pragma once

#include <vector>
#include <string>
#include <utility>

#include "wgc_flavour.h"
#include "wgc_client.h"

struct WGCInfo {
    std::wstring prefix;
    WgcFlavour flavour;
    std::wstring path_filename;
    std::wstring exe_filename;
};

class WgcFinder {
public:
    WgcFinder() = delete;
    ~WgcFinder() = delete;

    static std::vector<WgcClient> GetWgcClients();

private:
    static std::vector<WGCInfo> _wgcs;
};
