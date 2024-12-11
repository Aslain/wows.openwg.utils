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

    HBITMAP BitmapBlend(HBITMAP im1_bitmap, HBITMAP im2_bitmap)
    {
        if (!im1_bitmap || !im2_bitmap)
        {
            return nullptr;
        }

        // Get the dimensions of the bitmaps
        int im1_w, im1_h, im2_w, im2_h, im3_w, im3_h;
        if (!BitmapGetSize(im1_bitmap, &im1_w, &im1_h))
        {
            return nullptr;
        }
        if (!BitmapGetSize(im2_bitmap, &im2_w, &im2_h))
        {
            return nullptr;
        }
        im3_w = std::max(im1_w, im2_w);
        im3_h = std::max(im1_h, im2_h);

        // Create a compatible DC
        HDC hdcScreen = GetDC(nullptr);
        HDC im1_dc = CreateCompatibleDC(hdcScreen);
        HDC im2_dc = CreateCompatibleDC(hdcScreen);
        HDC im3_dc = CreateCompatibleDC(hdcScreen);

        // Select the bitmaps into the DCs
        HBITMAP im1_bitmap_old = (HBITMAP)SelectObject(im1_dc, im1_bitmap);
        HBITMAP im2_bitmap_old = (HBITMAP)SelectObject(im2_dc, im2_bitmap);

        // Create a new bitmap for the result
        HBITMAP im3_bitmap = CreateCompatibleBitmap(hdcScreen, im3_w, im3_h);
        HBITMAP im3_bitmap_old = (HBITMAP)SelectObject(im3_dc, im3_bitmap);

        // Scale the bitmaps if necessary
        StretchBlt(im1_dc, 0, 0, im3_w, im3_h, im1_dc, 0, 0, im1_w, im1_h, SRCCOPY);
        StretchBlt(im2_dc, 0, 0, im3_w, im3_h, im2_dc, 0, 0, im2_w, im2_h, SRCCOPY);

        // Blend the bitmaps
        BLENDFUNCTION blendFunction;
        blendFunction.BlendOp = AC_SRC_OVER;
        blendFunction.BlendFlags = 0;
        blendFunction.SourceConstantAlpha = 255;
        blendFunction.AlphaFormat = AC_SRC_ALPHA;

        GdiAlphaBlend(im3_dc, 0, 0, im3_w, im3_h, im1_dc, 0, 0, im3_w, im3_h, blendFunction);
        GdiAlphaBlend(im3_dc, 0, 0, im3_w, im3_h, im2_dc, 0, 0, im3_w, im3_h, blendFunction);

        // Clean up
        SelectObject(im1_dc, im1_bitmap_old);
        SelectObject(im2_dc, im2_bitmap_old);
        SelectObject(im3_dc, im3_bitmap_old);

        DeleteDC(im1_dc);
        DeleteDC(im2_dc);
        DeleteDC(im3_dc);
        ReleaseDC(nullptr, hdcScreen);

        return im3_bitmap;
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

    bool BitmapFree(HBITMAP bitmap)
    {
        if (!bitmap)
        {
            return false;
        }

        return DeleteObject(bitmap) != FALSE;
    }

    HBITMAP BitmapResize(HBITMAP bitmap, int width, int height)
    {
        // Get the dimensions
        int width_old, height_old;
        if (!BitmapGetSize(bitmap, &width_old, &height_old))
        {
            return nullptr;
        }

        // Create a compatible DC for the source bitmap
        HDC hdcScreen = GetDC(nullptr);
        HDC hdcSource = CreateCompatibleDC(hdcScreen);
        HDC hdcDest = CreateCompatibleDC(hdcScreen);

        // Select the source bitmap into the source DC
        HBITMAP hOldSourceBitmap = (HBITMAP)SelectObject(hdcSource, bitmap);

        // Create a new bitmap for the destination with the desired dimensions
        HBITMAP hBitmapDest = CreateCompatibleBitmap(hdcScreen, width, height);
        HBITMAP hOldDestBitmap = (HBITMAP)SelectObject(hdcDest, hBitmapDest);

        // Use StretchBlt to copy and resize the source bitmap into the destination bitmap
        StretchBlt(hdcDest, 0, 0, width, height, hdcSource, 0, 0, width_old, height_old, SRCCOPY);

        // Clean up and release resources
        SelectObject(hdcSource, hOldSourceBitmap);
        SelectObject(hdcDest, hOldDestBitmap);
        DeleteDC(hdcSource);
        DeleteDC(hdcDest);
        ReleaseDC(nullptr, hdcScreen);

        return hBitmapDest;
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
