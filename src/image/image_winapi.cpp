// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

//
// Includes
//

// stdlib
#include <filesystem>

// winapi
#include <Windows.h>

// stb
#include <stb_image.h>

// openwg.utils
#include "image/image_winapi.h"



//
// Implementation
//

namespace OpenWG::Utils::Image
{
    void* LoadToBitmap(const wchar_t* filename)
    {
        if (!filename)
        {
            return nullptr;
        }

        return LoadToBitmap(std::filesystem::path(filename));
    }

    void* LoadToBitmap(const std::filesystem::path& path)
    {
        if (!std::filesystem::exists(path))
        {
            return nullptr;
        }

        int image_width = 0, image_height = 0, channels = 0;
        const int channels_desired = 4;
        char buffer[MAX_PATH]{};
#if defined(_MSC_VER)
        stbi_convert_wchar_to_utf8(buffer, sizeof(buffer), path.wstring().c_str());
#endif

        unsigned char *data = stbi_load(buffer, &image_width, &image_height, &channels, channels_desired);
        if (!data) {
            return nullptr;
        }

        //swap R and B channels
        for (int idx = 0; idx < image_width * image_height * channels_desired; idx += channels_desired) {
            std::swap(data[idx], data[idx + 2]);
        }

        auto* result = CreateBitmap(image_width, image_height, 1, channels_desired * 8, data);
        stbi_image_free(data);

        return result;
    }

    bool FreeBitmap(void* bitmap)
    {
        if (!bitmap)
        {
            return false;
        }

        return DeleteObject(bitmap) != FALSE;
    }
}