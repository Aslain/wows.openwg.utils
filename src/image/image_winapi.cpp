// SPDX-License-Identifier: MIT
// Copyright (c) 2024 OpenWG.Utils Contributors

//
// Includes
//

// stdlib
#include <array>
#include <filesystem>

// winapi
#include <Windows.h>

// stb
#include <stb_image.h>

// avie
#include <avir.h>
#include <lancir.h>

// openwg.utils
#include "image/image_winapi.h"



//
// Implementation
//

namespace OpenWG::Utils::Image
{
    //
    // Bitmap
    //

    bool BitmapAlphaPremultiply(HBITMAP h_bitmap)
    {
        if (!h_bitmap)
        {
            return false;
        }

        auto h_dc = GetDC(nullptr);
        if (!h_dc)
        {
            return false;
        }

        BITMAP bm{};
        GetObjectW(h_bitmap, sizeof(bm), &bm);

        std::vector<uint8_t> bitmap_info_arr( 256 * sizeof(RGBQUAD));
        auto* bitmap_info = reinterpret_cast<BITMAPINFO*>(bitmap_info_arr.data());
        bitmap_info->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);

        BOOL bRes = GetDIBits(h_dc, h_bitmap, 0, bm.bmHeight, nullptr, bitmap_info, DIB_RGB_COLORS);
        if (!bRes || bitmap_info->bmiHeader.biBitCount != 32) {
            ReleaseDC(nullptr, h_dc);
            return false;
        }

        std::vector<DWORD> bit_data(bm.bmWidth * bm.bmHeight);

        LPBYTE pData = reinterpret_cast<LPBYTE>(bit_data.data());

        GetDIBits(h_dc, h_bitmap, 0, bm.bmHeight, pData, bitmap_info, DIB_RGB_COLORS);
        for (int y = 0; y < bm.bmHeight; y++) {
            for (int x = 0; x < bm.bmWidth; x++) {
                pData[0] = (BYTE) ((DWORD) pData[0] * pData[3] / 255);
                pData[1] = (BYTE) ((DWORD) pData[1] * pData[3] / 255);
                pData[2] = (BYTE) ((DWORD) pData[2] * pData[3] / 255);
                pData += 4;
            }
        }

        if (SetDIBits(h_dc, h_bitmap, 0, bm.bmHeight, bit_data.data(), bitmap_info, DIB_RGB_COLORS) != bm.bmHeight)
        {
            ReleaseDC(nullptr, h_dc);
            return false;
        }

        ReleaseDC(nullptr, h_dc);
        return true;
    }

    bool BitmapBlend(HBITMAP im1_bitmap, HBITMAP im2_bitmap, int dst_x, int dst_y)
    {
        if (!im1_bitmap || !im2_bitmap)
        {
            return false;
        }

        // Get the dimensions of the bitmaps
        int im1_w, im1_h, im2_w, im2_h;
        if (!BitmapGetSize(im1_bitmap, &im1_w, &im1_h))
        {
            return false;
        }
        if (!BitmapGetSize(im2_bitmap, &im2_w, &im2_h))
        {
            return false;
        }

        // Create a compatible DC
        HDC hdcScreen = GetDC(nullptr);
        HDC im1_dc = CreateCompatibleDC(hdcScreen);
        HDC im2_dc = CreateCompatibleDC(hdcScreen);

        // Select the bitmaps into the DCs
        HBITMAP im1_bitmap_old = (HBITMAP)SelectObject(im1_dc, im1_bitmap);
        HBITMAP im2_bitmap_old = (HBITMAP)SelectObject(im2_dc, im2_bitmap);

        // Blend the bitmaps
        BLENDFUNCTION blendFunction;
        blendFunction.BlendOp = AC_SRC_OVER;
        blendFunction.BlendFlags = 0;
        blendFunction.SourceConstantAlpha = 255;
        blendFunction.AlphaFormat = AC_SRC_ALPHA;

        GdiAlphaBlend(im1_dc, dst_x, dst_y, im2_w, im2_h, im2_dc, 0, 0, im2_w, im2_h, blendFunction);

        // Clean up
        SelectObject(im1_dc, im1_bitmap_old);
        SelectObject(im2_dc, im2_bitmap_old);

        DeleteDC(im1_dc);
        DeleteDC(im2_dc);

        ReleaseDC(nullptr, hdcScreen);

        return true;
    }

    HBITMAP BitmapClone(HBITMAP bitmap)
    {
        return static_cast<HBITMAP>(CopyImage(bitmap, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR));
    }

    bool BitmapGetSize(HBITMAP h_bitmap, int* width, int* height)
    {
        if (!h_bitmap || !width || !height)
        {
            return false;
        }

        BITMAP bm{};
        if (GetObjectW(h_bitmap, sizeof(bm), &bm) == 0)
        {
            return false;
        }

        *width = bm.bmWidth;
        *height = bm.bmHeight;
        return true;
    }

    HBITMAP BitmapLoad(const wchar_t* filename)
    {
        if (!filename)
        {
            return nullptr;
        }

        return BitmapLoad(std::filesystem::path(filename));
    }

    HBITMAP BitmapLoad(const std::filesystem::path& path)
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

    HBITMAP BitmapMultiplyColor(HBITMAP h_bitmap, float r_scale, float g_scale, float b_scale, float a_scale)
    {
        const int channels = 4;

        if (!h_bitmap)
        {
            return nullptr;
        }

        BITMAP bm{};
        GetObjectW(h_bitmap, sizeof(bm), &bm);

        auto h_dc = GetDC(nullptr);
        if (!h_dc)
        {
            return nullptr;
        }

        std::vector<uint8_t> bitmap_info_arr(sizeof(BITMAPINFOHEADER)  + 256 * sizeof(RGBQUAD));
        auto* bitmap_info = reinterpret_cast<BITMAPINFO*>(bitmap_info_arr.data());
        bitmap_info->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bitmap_info->bmiHeader.biWidth = bm.bmWidth;
        bitmap_info->bmiHeader.biHeight = -bm.bmHeight;  // Negative to indicate top-down
        bitmap_info->bmiHeader.biPlanes = 1;
        bitmap_info->bmiHeader.biBitCount = 32;
        bitmap_info->bmiHeader.biCompression = BI_RGB;

        std::vector<uint8_t> bit_data(bm.bmWidth * bm.bmHeight * channels);
        if (!GetDIBits(h_dc, h_bitmap, 0, bm.bmHeight, bit_data.data(), bitmap_info, DIB_RGB_COLORS))
        {
            ReleaseDC(nullptr, h_dc);
            return nullptr;
        }

        ReleaseDC(nullptr, h_dc);

        // change color components

        auto* pData = reinterpret_cast<uint8_t*>(bit_data.data());
        for (int y = 0; y < bm.bmHeight; y++) {
            for (int x = 0; x < bm.bmWidth; x++) {
                //hbitmap uses BGRA
                pData[0] = std::clamp<uint8_t>(pData[0] * b_scale, 0, 255);
                pData[1] = std::clamp<uint8_t>(pData[1] * g_scale, 0, 255);
                pData[2] = std::clamp<uint8_t>(pData[2] * r_scale, 0, 255);
                pData[3] = std::clamp<uint8_t>(pData[3] * a_scale, 0, 255);
                pData += 4;
            }
        };

        return CreateBitmap(bm.bmWidth, bm.bmHeight, 1, channels * 8, bit_data.data());
    }

    bool BitmapFree(HBITMAP bitmap)
    {
        if (!bitmap)
        {
            return false;
        }

        return DeleteObject(bitmap) != FALSE;
    }

    HBITMAP BitmapResize(HBITMAP h_bitmap, int width, int height)
    {
        const int channels = 4;

        if (!h_bitmap)
        {
            return nullptr;
        }

        BITMAP bm{};
        GetObjectW(h_bitmap, sizeof(bm), &bm);
        if (width == bm.bmWidth && height == bm.bmHeight)
        {
            return BitmapClone(h_bitmap);
        }

        auto h_dc = GetDC(nullptr);
        if (!h_dc)
        {
            return nullptr;
        }

        std::vector<uint8_t> bitmap_info_arr(sizeof(BITMAPINFOHEADER)  + 256 * sizeof(RGBQUAD));
        auto* bitmap_info = reinterpret_cast<BITMAPINFO*>(bitmap_info_arr.data());
        bitmap_info->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bitmap_info->bmiHeader.biWidth = bm.bmWidth;
        bitmap_info->bmiHeader.biHeight = -bm.bmHeight;  // Negative to indicate top-down
        bitmap_info->bmiHeader.biPlanes = 1;
        bitmap_info->bmiHeader.biBitCount = 32;
        bitmap_info->bmiHeader.biCompression = BI_RGB;

        std::vector<uint8_t> bit_data(bm.bmWidth * bm.bmHeight * channels);
        if (!GetDIBits(h_dc, h_bitmap, 0, bm.bmHeight, bit_data.data(), bitmap_info, DIB_RGB_COLORS))
        {
            ReleaseDC(nullptr, h_dc);
            return nullptr;
        }

        ReleaseDC(nullptr, h_dc);

        // resize
        avir::CLancIR resizer;
        std::vector<uint8_t> buf(width*height * channels);

        if ( resizer.resizeImage(bit_data.data(), bm.bmWidth, bm.bmHeight, buf.data(), width, height, channels) != height)
        {
            return nullptr;
        }

        return CreateBitmap(width, height, 1, channels * 8, buf.data());
    }



    //
    // Brush
    //

    HBRUSH BrushCreate(HBITMAP bitmap)
    {
        if (!bitmap)
        {
            return nullptr;
        }
        return CreatePatternBrush(bitmap);
    }

    bool BrushFree(HBRUSH brush)
    {
        if (!brush)
        {
            return false;
        }

        return DeleteObject(brush) != FALSE;
    }
}
