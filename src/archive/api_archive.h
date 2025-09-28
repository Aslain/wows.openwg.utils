#pragma once

#ifdef __cplusplus
extern "C" {
#endif

//
// Includes
//

// stdlib
#include <stdint.h>

//openwg.utils
#include "common/api_common.h"


//
// Types
//

typedef struct ARCHIVE_FileContext {
    uint64_t uncompressed_size;
    uint64_t compressed_size;
    int64_t  modification_time;
    uint32_t index;
    uint32_t crc32;
    uint16_t method;
    uint8_t  is_directory;
    uint8_t  is_encrypted;
    uint8_t  is_supported;
    uint8_t  reserved;
} ARCHIVE_FileContext;


//
// Functions
//

XVMEXT_API_CALL void* ARCHIVE_OpenW(const wchar_t* filepath);
XVMEXT_API_CALL bool  ARCHIVE_EntryExistsW(void* archive, const wchar_t* entry);
XVMEXT_API_CALL bool  ARCHIVE_GetEntryInfoW(void* archive, const wchar_t* entry, ARCHIVE_FileContext* context);
XVMEXT_API_CALL bool  ARCHIVE_ExtractToFileW(void* archive, const wchar_t* entry, const wchar_t* destination);
XVMEXT_API_CALL bool  ARCHIVE_Close(void* archive);

#ifdef __cplusplus
    }
#endif
