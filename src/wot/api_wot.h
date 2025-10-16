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
    WoT_Branch_Unknown     = 0,
    WoT_Branch_Release     = 1 << 0,
    WoT_Branch_CommonTest  = 1 << 1,
    WoT_Branch_SuperTest   = 1 << 2,
    WoT_Branch_Sandbox     = 1 << 3,
    WoT_Branch_ClosedTest  = 1 << 4,

    WoT_Branch_All = WoT_Branch_Release | WoT_Branch_CommonTest | WoT_Branch_SuperTest | WoT_Branch_Sandbox | WoT_Branch_ClosedTest,
};

enum ClientType {
    WoT_Type_Unknown = 0,
    WoT_Type_SD = 1,
    WoT_Type_HD = 2,
};

enum ClientVendor {
    WoT_Vendor_Unknown = 0,
    WoT_Vendor_WG      = 1 << 0,
    WoT_Vendor_Lesta   = 1 << 1,
};

enum ClientCache
{
    WoT_Cache_Unknown = 0,
    WoT_Cache_PDC     = 1 << 0,
};

enum LauncherFlavour {
    Launcher_Flavour_Unknown    = 0,
    Launcher_Flavour_WGC        = 1,
    Launcher_Flavour_China360   = 2,
    Launcher_Flavour_Steam      = 3,
    Launcher_Flavour_LGC        = 4,
    Launcher_Flavour_Standalone = 5,
};

#if defined(__cplusplus)
inline ClientCache operator|(ClientCache a, ClientCache b)
{
    using underlying_t = typename std::underlying_type<ClientCache>::type;
    return static_cast<ClientCache>(static_cast<underlying_t>(a) | static_cast<underlying_t>(b));
}
#endif

//
// Functions/Discovery
//

/**
 * Set client branch filter
 * @param branch_filter   bitmask of allowed branches
 * @note it deletes all manually added clients and may change clients order
 * @return number of found clients
 */
XVMEXT_API_CALL int32_t WOT_Discovery_SetBranchFilter(int32_t branch_filter);


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
 * Set vendor filter and vendor priority
 * @param vendor_filter   bitmask of allowed vendors
 * @param vendor_priority select vendor which should be displayed first
 * @note it deletes all manually added clients and may change clients order
 * @return number of found clients
 */
XVMEXT_API_CALL int32_t WOT_LauncherSetDefault(int32_t vendor_filter, int32_t vendor_default);


/**
 * Find client by its path
 * @param path absolute path to the client
 * @return client index, -1 if client was not found
 */
XVMEXT_API_CALL int32_t WOT_ClientFind(const wchar_t* path);

/**
 * Checks that client is started
 * @param index client index, negative value to check all the registered clients
 * @return 1 if at least one client is started, 0 if client was not launched, -1 if client does not exists or error occurred
 */
XVMEXT_API_CALL int32_t WOT_ClientIsStarted(int32_t index);

/**
 * Checks that client version is match to the given pattern
 * @param index client index
 * @param pattern pattern to test, regex in ECMAScript syntax
 * @return 1 in case of matched pattern, 0 is not matched, -1 in case of error
 */
XVMEXT_API_CALL int32_t WOT_ClientIsVersionMatch(int32_t index, const wchar_t* pattern);

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
 * Get path to the client mods folder (including version part)
 * @param buffer buffer to save path, relative to the client root
 * @param buffer_size size of string buffer in wchars
 * @param index client index
 */
XVMEXT_API_CALL void WOT_GetClientPathModsW(wchar_t *buffer, int32_t buffer_size, int32_t index);


/**
 * Get path to the client res_mods folder (including version part)
 * @param buffer buffer to save path, relative to the client root
 * @param buffer_size size of string buffer in wchars
 * @param index client index
 */
XVMEXT_API_CALL void WOT_GetClientPathResmodsW(wchar_t *buffer, int32_t buffer_size, int32_t index);


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
 * Get client vendor
 * @param index client index
 * @return one of ::ClientVendor values or -1 in case of error
 */
XVMEXT_API_CALL int32_t WOT_GetClientVendor(int32_t index);

/**
 * Get client version
 * @param buffer buffer to save string
 * @param size size of string buffer in wchars
 * @param index client index
 */
XVMEXT_API_CALL void WOT_GetClientVersionW(wchar_t *buffer, int32_t size, int32_t index);


/**
 * Get client main executable name
 * @param buffer buffer to save string
 * @param size size of string buffer in wchars
 * @param index client index
 */
XVMEXT_API_CALL void WOT_GetClientExeNameW(wchar_t* buffer, int32_t size, int32_t index);


/**
 * Get client main executable version
 * @param buffer buffer to save string
 * @param size size of string buffer in wchars
 * @param index client index
 */
XVMEXT_API_CALL void WOT_GetClientExeVersionW(wchar_t *buffer, int32_t size, int32_t index);

//
// Functions / Client / Cache
//

/**
 * Get type of caches which are existed
 * @param index client index
 * @return bitmask of ::ClientCache values or -1 in case of error
 */
XVMEXT_API_CALL int32_t WOT_GetClientCachePresent(int32_t index);


/**
 * Get type of caches which are supported by client
 * @param index client index
 * @return bitmask of ::ClientCache values or -1 in case of error
 */
XVMEXT_API_CALL int32_t WOT_GetClientCacheSupported(int32_t index);

/**
 * Clear given types of client caches
 * @param index client index
 * @param cache_type bitmask of ::ClientCache
 * @return 1 if caches were cleared, 0 if caches were not cleared, -1 in case of error
 */
XVMEXT_API_CALL int32_t WOT_ClearClientCache(int32_t index, ClientCache cache_type);

/**
 * Extract a file from a package to destination path on disk.
 * @param index client index
 * @param package_relative_path path to package, relative to client root
 * @param entry_path entry path inside the package
 * @param destination_path destination path on disk
 * @return 1 if extraction succeeded, 0 if extraction failed, -1 in case of error
 */
XVMEXT_API_CALL int32_t WOT_ClientExtractPackageFileToFileW(int32_t index,
                                                            const wchar_t* package_relative_path,
                                                            const wchar_t* entry_path,
                                                            const wchar_t* destination_path);

/**
 * Get number of package definitions for the client.
 * @param index client index
 * @return number of packages, or -1 in case of error
 */
XVMEXT_API_CALL int32_t WOT_ClientGetPackagesCount(int32_t index);

/**
 * Get package path by index.
 * @param index client index
 * @param package_index zero-based package index
 * @param buffer destination buffer for package path
 * @param buffer_size size of buffer in wchars
 * @return 1 on success, 0 if package index is invalid, -1 in case of error
 */
XVMEXT_API_CALL int32_t WOT_ClientGetPackagePathW(int32_t index,
                                                  int32_t package_index,
                                                  wchar_t* buffer,
                                                  int32_t buffer_size);


#ifdef __cplusplus
}
#endif
