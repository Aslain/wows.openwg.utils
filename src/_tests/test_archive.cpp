// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

//
// Includes
//

#define NOMINMAX
#include <windows.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <miniz.h>
#include <catch2/catch_test_macros.hpp>

#include "archive/api_archive.h"

namespace {
    std::string to_utf8(const std::wstring& value) {
        if (value.empty()) {
            return {};
        }

        int required = WideCharToMultiByte(
            CP_UTF8,
            0,
            value.c_str(),
            static_cast<int>(value.size()),
            nullptr,
            0,
            nullptr,
            nullptr);

        if (required <= 0) {
            return {};
        }

        std::string result(static_cast<size_t>(required), '\0');
        WideCharToMultiByte(
            CP_UTF8,
            0,
            value.c_str(),
            static_cast<int>(value.size()),
            result.data(),
            required,
            nullptr,
            nullptr);

        return result;
    }

    std::filesystem::path create_sample_archive(const std::filesystem::path& archive_path,
                                                const char* entry_name,
                                                const char* entry_content) {
        std::filesystem::create_directories(archive_path.parent_path());

        const std::string archive_path_u8 = to_utf8(archive_path.wstring());

        mz_zip_archive zip{};
        REQUIRE(mz_zip_writer_init_file(&zip, archive_path_u8.c_str(), 0) == MZ_TRUE);

        const size_t entry_size = std::char_traits<char>::length(entry_content);
        REQUIRE(mz_zip_writer_add_mem(&zip, entry_name, entry_content, entry_size, MZ_NO_COMPRESSION) == MZ_TRUE);
        REQUIRE(mz_zip_writer_finalize_archive(&zip) == MZ_TRUE);
        REQUIRE(mz_zip_writer_end(&zip) == MZ_TRUE);

        return archive_path;
    }
}


//
// Test
//

TEST_CASE("archive_api", "[archive]") {
    SECTION("null_arguments") {
        REQUIRE(ARCHIVE_OpenW(nullptr) == nullptr);
        REQUIRE_FALSE(ARCHIVE_EntryExistsW(nullptr, L"entry"));
        REQUIRE_FALSE(ARCHIVE_GetEntryInfoW(nullptr, L"entry", nullptr));
        REQUIRE_FALSE(ARCHIVE_ExtractToFileW(nullptr, L"entry", L"path"));
        REQUIRE_FALSE(ARCHIVE_Close(nullptr));
    }

    SECTION("end_to_end_extract") {
        const auto temp_root = std::filesystem::temp_directory_path();
        const auto unique_suffix = std::chrono::steady_clock::now().time_since_epoch().count();
        const auto temp_dir = temp_root / ("openwg_archive_test_" + std::to_string(unique_suffix));
        std::filesystem::create_directories(temp_dir);

        constexpr const char* kEntryName = "docs/readme.txt";
        constexpr const char* kEntryContent = "miniz archive content";
        const size_t entry_size = std::char_traits<char>::length(kEntryContent);

        const auto archive_path = create_sample_archive(temp_dir / "sample.zip", kEntryName, kEntryContent);

        auto* archive_handle = ARCHIVE_OpenW(archive_path.wstring().c_str());
        REQUIRE(archive_handle != nullptr);

        REQUIRE(ARCHIVE_EntryExistsW(archive_handle, L"docs/readme.txt"));

        ARCHIVE_FileContext context{};
        REQUIRE(ARCHIVE_GetEntryInfoW(archive_handle, L"docs/readme.txt", &context));
        CHECK(context.uncompressed_size == entry_size);
        CHECK(context.compressed_size == entry_size);
        CHECK(context.index == 0);
        CHECK(context.method == 0);
        CHECK(context.is_directory == 0);
        CHECK(context.is_encrypted == 0);
        CHECK(context.is_supported == 1);

        const auto extract_path = temp_dir / "output.txt";
        std::filesystem::create_directories(extract_path.parent_path());
        REQUIRE(ARCHIVE_ExtractToFileW(archive_handle, L"docs/readme.txt", extract_path.wstring().c_str()));

        std::ifstream extracted_file(extract_path, std::ios::binary);
        REQUIRE(extracted_file.is_open());
        const std::string extracted_content(
            (std::istreambuf_iterator<char>(extracted_file)),
            std::istreambuf_iterator<char>());

        CHECK(extracted_content == std::string(kEntryContent, entry_size));

        REQUIRE(ARCHIVE_Close(archive_handle));

        std::filesystem::remove(extract_path);
        std::filesystem::remove(archive_path);
        std::filesystem::remove(temp_dir);
    }

    SECTION("extract_to_memory") {
        const auto temp_root = std::filesystem::temp_directory_path();
        const auto unique_suffix = std::chrono::steady_clock::now().time_since_epoch().count();
        const auto temp_dir = temp_root / ("openwg_archive_test_mem_" + std::to_string(unique_suffix));
        std::filesystem::create_directories(temp_dir);

        constexpr const char* kEntryName = "content/data.bin";
        constexpr const char* kEntryContent = "binary payload";
        const size_t entry_size = std::char_traits<char>::length(kEntryContent);

        const auto archive_path = create_sample_archive(temp_dir / "memory.zip", kEntryName, kEntryContent);

        auto* archive_handle = ARCHIVE_OpenW(archive_path.wstring().c_str());
        REQUIRE(archive_handle != nullptr);

        const std::wstring entry_w = std::wstring(kEntryName, kEntryName + std::char_traits<char>::length(kEntryName));

        ARCHIVE_FileContext context{};
        REQUIRE(ARCHIVE_GetEntryInfoW(archive_handle, entry_w.c_str(), &context));
        CHECK(context.uncompressed_size == entry_size);

        // Too small buffer
        uint64_t bytes_written = 0;
        std::vector<char> small_buffer(entry_size / 2 + (entry_size == 1 ? 1 : 0));
        REQUIRE_FALSE(ARCHIVE_ExtractToMemory(archive_handle,
                                              entry_w.c_str(),
                                              small_buffer.data(),
                                              static_cast<uint64_t>(small_buffer.size()),
                                              &bytes_written));
        CHECK(bytes_written == entry_size);

        // Correct buffer size
        std::vector<char> buffer(entry_size);
        bytes_written = 0;
        REQUIRE(ARCHIVE_ExtractToMemory(archive_handle,
                                        entry_w.c_str(),
                                        buffer.data(),
                                        static_cast<uint64_t>(buffer.size()),
                                        &bytes_written));
        CHECK(bytes_written == entry_size);
        CHECK(std::string(buffer.begin(), buffer.end()) == std::string(kEntryContent, entry_size));

        REQUIRE(ARCHIVE_Close(archive_handle));

        std::filesystem::remove(archive_path);
        std::filesystem::remove(temp_dir);
    }
}
