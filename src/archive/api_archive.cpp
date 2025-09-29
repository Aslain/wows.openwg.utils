//
// Includes
//

#include <miniz.h>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <filesystem>
#include <limits>
#include <string>
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

uint32_t ARCHIVE_GetEntriesCount(void *archive_ptr) {
    if (!archive_ptr) {
        return 0;
    }

    auto* archive = static_cast<mz_zip_archive*>(archive_ptr);
    mz_uint num_files = mz_zip_reader_get_num_files(archive);
    return static_cast<uint32_t>(num_files);
}

uint32_t ARCHIVE_GetEntryNameW(void *archive_ptr,
                               uint32_t index,
                               wchar_t *buffer,
                               uint32_t buffer_size) {
    if (!archive_ptr) {
        if (buffer && buffer_size > 0) {
            buffer[0] = L'\0';
        }
        return 0;
    }

    auto* archive = static_cast<mz_zip_archive*>(archive_ptr);
    mz_uint num_files = mz_zip_reader_get_num_files(archive);
    if (index >= num_files) {
        if (buffer && buffer_size > 0) {
            buffer[0] = L'\0';
        }
        return 0;
    }

    mz_zip_archive_file_stat stat{};
    if (mz_zip_reader_file_stat(archive, index, &stat) != MZ_TRUE) {
        if (buffer && buffer_size > 0) {
            buffer[0] = L'\0';
        }
        return 0;
    }

    std::string filename_utf8(stat.m_filename ? stat.m_filename : "");
    std::wstring filename_wide = Encoding::utf8_to_wstring(filename_utf8);
    uint32_t required_size = static_cast<uint32_t>(filename_wide.size() + 1);

    if (!buffer || buffer_size == 0) {
        return required_size;
    }

    if (buffer_size < required_size) {
        buffer[0] = L'\0';
        return required_size;
    }

    std::wmemcpy(buffer, filename_wide.c_str(), filename_wide.size());
    buffer[filename_wide.size()] = L'\0';
    return required_size;
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

bool ARCHIVE_ExtractToMemory(void *archive_ptr,
                             const wchar_t *entry,
                             void *destination,
                             uint64_t destination_size,
                             uint64_t *bytes_written) {
    if (!archive_ptr) {
        return false;
    }
    if (!entry) {
        return false;
    }

    auto *archive = static_cast<mz_zip_archive *>(archive_ptr);
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
        if (bytes_written) {
            *bytes_written = 0;
        }
        return false;
    }

    if (bytes_written) {
        *bytes_written = stat.m_uncomp_size;
    }

    if (stat.m_uncomp_size == 0) {
        return true;
    }

    if (stat.m_uncomp_size > std::numeric_limits<size_t>::max()) {
        return false;
    }

    size_t required_size = static_cast<size_t>(stat.m_uncomp_size);
    if (!destination || destination_size < stat.m_uncomp_size || required_size == 0) {
        return false;
    }

    mz_bool result = mz_zip_reader_extract_to_mem(archive, file_index, destination, required_size, 0);
    if (result != MZ_TRUE) {
        return false;
    }

    if (bytes_written) {
        *bytes_written = stat.m_uncomp_size;
    }

    return true;
}
