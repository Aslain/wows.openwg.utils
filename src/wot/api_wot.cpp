// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

//
// Includes
//

#include <memory>
#include <vector>

#include "wot/api_wot.h"
#include "wot/client_interface.h"
#include "wot/launcher_factory.h"
#include "wot/launcher_standalone.h"

using namespace OpenWG::Utils::WoT;



//
// globals
//

int32_t g_vendor_default = ClientVendor::WoT_Vendor_WG;
int32_t g_vendor_filter = ClientVendor::WoT_Vendor_WG | ClientVendor::WoT_Vendor_Lesta;

std::vector<std::shared_ptr<LauncherInterface>> g_launchers{};
std::vector<std::shared_ptr<ClientInterface>> g_clients{};



//
// Private
//

void clients_rescan() {
    g_clients.clear();
    for (auto &launcher: g_launchers) {
        launcher->Rescan();
        for (auto &client: launcher->GetClients()) {
            // check that it is already existing
            bool exists = false;
            for (auto &client_existing: g_clients) {
                if (std::filesystem::equivalent(client_existing->GetPath(), client->GetPath())) {
                    exists = true;
                    break;
                }
            }
            if (exists) {
                continue;
            }

            // check for filter
            if ((client->GetVendor() & g_vendor_filter) == 0) {
                continue;
            }

            // add client
            g_clients.push_back(client);
        }
    }
}

void launchers_init() {
    if (g_launchers.empty()) {
        g_launchers = OpenWG::Utils::WoT::LauncherFactory::getLaunchers(static_cast<ClientVendor>(g_vendor_default));
        clients_rescan();
    }
}

//
// API
//

int32_t WOT_AddClientW(const wchar_t *path) {
    int32_t result{-1};

    launchers_init();
    if (path) {
        auto path_normalized = std::filesystem::path(path).lexically_normal();

        for (int32_t idx = 0; idx < g_clients.size(); idx++) {
            if (g_clients[idx] && g_clients[idx]->GetPath() == path_normalized) {
                result = idx;
                break;
            }
        }

        if (result < 0) {
            for (auto &launcher: g_launchers) {
                if (!launcher || launcher->GetFlavour() != Launcher_Flavour_Standalone) {
                    continue;
                }

                // create client
                auto client = std::make_shared<ClientWoT>(path, launcher->GetFlavour());
                if (!client->IsValid()) {
                    break;
                }
                if ((client->GetVendor() & g_vendor_filter) == 0) {
                    break;
                }

                // connect to launcher
                if (dynamic_cast<LauncherStandalone &>(*launcher).AddClient(client)) {
                    g_clients.push_back(launcher->GetClients().back());
                    result = g_clients.size() - 1;
                    break;
                }
            }
        }
    }

    return result;
}


int32_t WOT_LauncherGetPreferredClient(int32_t launcher_type) {
    int32_t result{-1};

    launchers_init();

    for (int32_t idx = 0; idx < g_clients.size(); idx++) {
        auto &client = g_clients[idx];
        if (client->GetLauncherFlavour() == static_cast<LauncherFlavour>(launcher_type)) {
            result = idx;
            break;
        }
    }

    return result;
}


int32_t WOT_LauncherRescan() {
    g_launchers.clear();
    return WOT_GetClientsCount();
}


int32_t WOT_LauncherSetDefault(int32_t vendor_filter, int32_t vendor_default) {
    g_vendor_filter = vendor_filter;
    g_vendor_default = vendor_default;
    if ((g_vendor_default & g_vendor_filter) == 0) {
        g_vendor_default = g_vendor_filter;
    }

    return WOT_LauncherRescan();
}


int32_t WOT_ClientFind(const wchar_t *path) {
    int32_t result{-1};
    launchers_init();

    if(path != nullptr) {
        auto path_norm = std::filesystem::path(path).lexically_normal();
        for (int32_t idx = 0; idx < g_clients.size(); idx++) {
            auto &client = g_clients[idx];
            if (client->GetPath() == path_norm) {
                result = idx;
                break;
            }
        }
    }

    return result;
}

int32_t WOT_ClientIsStarted(int32_t index) {
    int32_t result = -1;

    launchers_init();

    if (index < 0) {
        result = 0;
        for (auto &client: g_clients) {
            result = result || (client && client->IsStarted());
        }
    }
    if (index < g_clients.size() && g_clients[index]) {
        result = g_clients[index]->IsStarted();
    }

    return result;
}

int32_t WOT_ClientIsVersionMatch(int32_t index, const wchar_t *pattern) {
    int32_t result = -1;

    launchers_init();

    if (index < g_clients.size() && g_clients[index]) {
        result = g_clients[index]->IsVersionMatch(pattern);
    }

    return result;
}

int32_t WOT_ClientTerminate(int32_t index) {
    int32_t result = -1;

    launchers_init();

    if (index < 0) {
        result = 0;
        for (auto &client: g_clients) {
            result = result || client->Terminate();
        }
    } else if (index < g_clients.size() && g_clients[index]) {
        result = g_clients[index]->Terminate();
    }

    return result;
}


int32_t WOT_GetClientsCount() {
    launchers_init();
    return static_cast<int32_t>(g_clients.size());
}


int32_t WOT_GetClientBranch(int32_t index) {
    int32_t result = -1;

    launchers_init();

    if (index >= 0 && index < g_clients.size() && g_clients[index]) {
        result = g_clients[index]->GetBranch();
    }

    return result;
}


int32_t WOT_GetClientLauncherFlavour(int32_t index) {
    int32_t result = -1;

    launchers_init();

    if (index >= 0 && index < g_clients.size() && g_clients[index]) {
        result = g_clients[index]->GetLauncherFlavour();
    }

    return result;
}


void WOT_GetClientLocaleW(wchar_t *buffer, int32_t buffer_size, int32_t index) {
    launchers_init();

    if (buffer == nullptr || buffer_size <= 0 || index < 0) {
        return;
    }

    buffer[0] = '\0';
    if (index < g_clients.size() && g_clients[index]) {
        wcscpy_s(buffer, buffer_size, g_clients[index]->GetLocale().c_str());
    }
}


void WOT_GetClientPathW(wchar_t *buffer, int32_t buffer_size, int32_t index) {
    launchers_init();

    if (buffer == nullptr || buffer_size <= 0 || index < 0) {
        return;
    }

    buffer[0] = '\0';
    if (index < g_clients.size() && g_clients[index]) {
        wcscpy_s(buffer, buffer_size, g_clients[index]->GetPath().c_str());
    }
}


void WOT_GetClientPathModsW(wchar_t *buffer, int32_t buffer_size, int32_t index) {
    launchers_init();

    if (buffer == nullptr || buffer_size <= 0 || index < 0) {
        return;
    }

    buffer[0] = '\0';
    if (index < g_clients.size() && g_clients[index]) {
        wcscpy_s(buffer, buffer_size, g_clients[index]->GetPathMods().c_str());
    }
}


void WOT_GetClientPathResmodsW(wchar_t *buffer, int32_t buffer_size, int32_t index) {
    launchers_init();

    if (buffer == nullptr || buffer_size <= 0 || index < 0) {
        return;
    }

    buffer[0] = '\0';
    if (index < g_clients.size() && g_clients[index]) {
        wcscpy_s(buffer, buffer_size, g_clients[index]->GetPathResmods().c_str());
    }
}


void WOT_GetClientRealmW(wchar_t *buffer, int32_t buffer_size, int32_t index) {
    launchers_init();

    if (buffer == nullptr || buffer_size <= 0 || index < 0) {
        return;
    }

    buffer[0] = '\0';
    if (index < g_clients.size() && g_clients[index]) {
        wcscpy_s(buffer, buffer_size, g_clients[index]->GetRealm().c_str());
    }
}


int32_t WOT_GetClientType(int32_t index) {
    int32_t result = -1;

    launchers_init();

    if (index >= 0 && index < g_clients.size() && g_clients[index]) {
        result = g_clients[index]->GetType();
    }

    return result;
}


int32_t WOT_GetClientVendor(int32_t index) {
    int32_t result = -1;

    launchers_init();

    if (index >= 0 && index < g_clients.size() && g_clients[index]) {
        result = g_clients[index]->GetVendor();
    }

    return result;
}


void WOT_GetClientVersionW(wchar_t *buffer, int32_t buffer_size, int32_t index) {
    launchers_init();

    if (buffer == nullptr || buffer_size <= 0 || index < 0) {
        return;
    }

    buffer[0] = '\0';
    if (index < g_clients.size() && g_clients[index]) {
        wcscpy_s(buffer, buffer_size, g_clients[index]->GetVersionClient().c_str());
    }
}


void WOT_GetClientExeNameW(wchar_t* buffer, int32_t buffer_size, int32_t index) {
    launchers_init();

    if (buffer == nullptr || buffer_size <= 0 || index < 0) {
        return;
    }

    buffer[0] = '\0';
    if (index < g_clients.size() && g_clients[index]) {
        wcscpy_s(buffer, buffer_size, g_clients[index]->GetExeName().c_str());
    }
}


void WOT_GetClientExeVersionW(wchar_t *buffer, int32_t buffer_size, int32_t index) {
    launchers_init();

    if (buffer == nullptr || buffer_size <= 0 || index < 0) {
        return;
    }

    buffer[0] = '\0';
    if (index < g_clients.size() && g_clients[index]) {
        wcscpy_s(buffer, buffer_size, g_clients[index]->GetVersionExe().c_str());
    }
}
