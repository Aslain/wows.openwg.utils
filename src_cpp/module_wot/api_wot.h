// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "common/api_common.h"

//
// Enums
//

enum ClientBranch {
    WoT_Branch_Unknown = 0,
    WoT_Branch_Release = 1,
    WoT_Branch_CommonTest = 2,
    WoT_Branch_SuperTest = 3,
    WoT_Branch_Sandbox = 4,
};

enum ClientType {
    WoT_Type_Unknown = 0,
    WoT_Type_SD = 1,
    WoT_Type_HD = 2,
};

enum LauncherFlavour {
    Launcher_Flavour_Unknown = 0,
    Launcher_Flavour_WG = 1,
    Launcher_Flavour_China360 = 2,
    Launcher_Flavour_Steam = 3,
    Launcher_Flavour_Lesta = 4,
    Launcher_Flavour_Standalone = 5,
};

//
// Functions
//

/**
 * Adds new client to the
 * @param path path to the client
 * @return index of new client, -1 in case of error
 */
XVMEXT_API_CALL int32_t WOT_AddClientW(const wchar_t *path);

/**
 * Get client preferred by launcher
 * @param launcher_flavour one of ::LauncherFlavour values
 * @return index of preferred client, -1 in case of non-existent launcher or error
 */
XVMEXT_API_CALL int32_t WOT_LauncherGetPreferredClient(int32_t launcher_flavour);

/**
 * Rescan launchers for new clients
 * @note it deletes all manually added clients and may change clients order
 * @return number of found clients
 */
XVMEXT_API_CALL int32_t WOT_LauncherRescan();

/**
 * Set default launcher flavour and rescan for new clients
 * @note it deletes all manually added clients and may change clients order
 * @return number of found clients
 */
XVMEXT_API_CALL int32_t WOT_LauncherSetDefault(int32_t launcher_flavour);

/**
 * Checks that client is started
 * @param index client index, negative value to check all the registered clients
 * @return 1 if at least one client is started, 0 if client was not launched, -1 if client does not exists or error occurred
 */
XVMEXT_API_CALL int32_t WOT_ClientIsStarted(int32_t index);

/**
 * Terminate client
 * @param index client index, negative value to terminate all the registered clients
 * @return 1 if at least one client was terminated, 0 if clients was not terminated, -1 if client does not exists or error occurred
 */
XVMEXT_API_CALL int32_t WOT_ClientTerminate(int32_t index);

/**
 * Get count of clients
 * @return number of clients
 */
XVMEXT_API_CALL int32_t WOT_GetClientsCount();

/**
 * Get client branch
 * @param index client index
 * @return one of ::ClientBranch values or -1 in case of error
 */
XVMEXT_API_CALL int32_t WOT_GetClientBranch(int32_t index);

/**
 * Get type of launcher which controls client
 * @param index client index
 * @return one of ::LauncherFlavour values or -1 in case of error
 */
XVMEXT_API_CALL int32_t WOT_GetClientLauncherFlavour(int32_t index);

/**
 * Get client locale in IETF BCP47 uppercase
 * @param buffer buffer to save string
 * @param buffer_size size of string buffer in wchars
 * @param index client index
 */
XVMEXT_API_CALL void WOT_GetClientLocaleW(wchar_t *buffer, int32_t buffer_size, int32_t index);

/**
 * Get path to the client
 * @param buffer buffer to save string
 * @param buffer_size size of string buffer in wchars
 * @param index client index
 */
XVMEXT_API_CALL void WOT_GetClientPathW(wchar_t *buffer, int32_t buffer_size, int32_t index);


/**
 * Get the realm of the client
 * @param buffer buffer to save string
 * @param buffer_size size of string buffer in wchars
 * @param index client index
 */
XVMEXT_API_CALL void WOT_GetClientRealmW(wchar_t *buffer, int32_t buffer_size, int32_t index);

/**
 * Get client type
 * @param index client index
 * @return one of ::ClientType values or -1 in case of error
 */
XVMEXT_API_CALL int32_t WOT_GetClientType(int32_t index);

/**
 * Get client version
 * @param buffer buffer to save string
 * @param size size of string buffer in wchars
 * @param index client index
 */
XVMEXT_API_CALL void WOT_GetClientVersionW(wchar_t *buffer, int32_t size, int32_t index);

/**
 * Get client main executable version
 * @param buffer buffer to save string
 * @param size size of string buffer in wchars
 * @param index client index
 */
XVMEXT_API_CALL void WOT_GetClientExeVersionW(wchar_t *buffer, int32_t size, int32_t index);

#ifdef __cplusplus
}
#endif
