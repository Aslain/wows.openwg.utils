//
// Includes
//

#include <miniz.h>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <system_error>

#include "archive/api_archive.h"
#include "common/encoding.h"
#include "fs/api_fs.h"

static_assert(sizeof(ARCHIVE_FileContext) == 40, "ARCHIVE_FileContext size mismatch");


//
// Functions
//

void * ARCHIVE_OpenW(const wchar_t* filepath) {
    if (!filepath) {
        return nullptr;
    }

    if (!FS_FileExistsW(filepath)) {
        return nullptr;
    }

    auto* archive = static_cast<mz_zip_archive*>(calloc(1, sizeof(mz_zip_archive)));
    if (!archive) {
        return nullptr;
    }

    auto filepath_u8 = Encoding::wstring_to_utf8(filepath);
    mz_bool result = mz_zip_reader_init_file(archive, filepath_u8.c_str(), 0);
    if (!result) {
        free(archive);
        return nullptr;
    }

    return archive;
}


bool ARCHIVE_Close(void *archive_ptr) {
    if (!archive_ptr) {
        return false;
    }

    auto* archive = static_cast<mz_zip_archive*>(archive_ptr);
    mz_bool end_result = mz_zip_reader_end(archive);
    free(archive);

    return end_result == MZ_TRUE;
}

bool ARCHIVE_EntryExistsW(void *archive_ptr, const wchar_t *entry) {
    if (!archive_ptr) {
        return false;
    }
    if (!entry) {
        return false;
    }

    auto* archive = static_cast<mz_zip_archive*>(archive_ptr);
    auto entry_u8 = Encoding::wstring_to_utf8(entry);
    return mz_zip_reader_locate_file_v2(archive, entry_u8.c_str(), nullptr, 0, nullptr) == MZ_TRUE;
}

bool ARCHIVE_GetEntryInfoW(void *archive_ptr, const wchar_t *entry, ARCHIVE_FileContext *context) {
    if (!archive_ptr) {
        return false;
    }
    if (!entry) {
        return false;
    }
    if (!context) {
        return false;
    }

    auto* archive = static_cast<mz_zip_archive*>(archive_ptr);
    auto entry_u8 = Encoding::wstring_to_utf8(entry);

    mz_uint32 file_index = 0;
    if (mz_zip_reader_locate_file_v2(archive, entry_u8.c_str(), nullptr, 0, &file_index) != MZ_TRUE) {
        return false;
    }

    mz_zip_archive_file_stat stat{};
    if (mz_zip_reader_file_stat(archive, file_index, &stat) != MZ_TRUE) {
        return false;
    }

    std::memset(context, 0, sizeof(*context));
    context->uncompressed_size = stat.m_uncomp_size;
    context->compressed_size = stat.m_comp_size;
#if defined(MINIZ_NO_TIME)
    context->modification_time = 0;
#else
    context->modification_time = static_cast<int64_t>(stat.m_time);
#endif
    context->index = file_index;
    context->crc32 = stat.m_crc32;
    context->method = stat.m_method;
    context->is_directory = static_cast<uint8_t>(stat.m_is_directory ? 1 : 0);
    context->is_encrypted = static_cast<uint8_t>(stat.m_is_encrypted ? 1 : 0);
    context->is_supported = static_cast<uint8_t>(stat.m_is_supported ? 1 : 0);
    context->reserved = 0;

    return true;
}

bool ARCHIVE_ExtractToFileW(void *archive_ptr, const wchar_t *entry, const wchar_t *destination) {
    if (!archive_ptr) {
        return false;
    }
    if (!entry) {
        return false;
    }
    if (!destination) {
        return false;
    }

    auto* archive = static_cast<mz_zip_archive*>(archive_ptr);
    auto entry_u8 = Encoding::wstring_to_utf8(entry);

    mz_uint32 file_index = 0;
    if (mz_zip_reader_locate_file_v2(archive, entry_u8.c_str(), nullptr, 0, &file_index) != MZ_TRUE) {
        return false;
    }

    mz_zip_archive_file_stat stat{};
    if (mz_zip_reader_file_stat(archive, file_index, &stat) != MZ_TRUE) {
        return false;
    }

    if (!stat.m_is_supported || stat.m_is_directory) {
        return false;
    }

    std::filesystem::path destination_path(destination);
    if (!destination_path.parent_path().empty()) {
        std::error_code ec;
        std::filesystem::create_directories(destination_path.parent_path(), ec);
        if (ec) {
            return false;
        }
    }

    auto destination_u8 = Encoding::wstring_to_utf8(destination_path.wstring());
    mz_bool result = mz_zip_reader_extract_to_file(archive, file_index, destination_u8.c_str(), 0);
    return result == MZ_TRUE;
}
