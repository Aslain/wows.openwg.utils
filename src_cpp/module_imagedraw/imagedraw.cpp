/* Copyright (c) 2017-2021, Mikhail Paulyshka.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "imagedraw.h"
#include "common/encoding.h"

#include <fstream>

#include <lodepng.h>



//Input image must be RGB buffer (3 bytes per pixel), but you can easily make it
//support RGBA input and output by changing the inputChannels and/or outputChannels
//in the function to 4.
void encodeBMP(std::vector<uint8_t>& bmp, const uint8_t* image, uint16_t w, uint16_t h)
{
    bmp = { 'B', 'M' ,                                //0: bfType
             0, 0, 0, 0,                              //2: bfSize; size not yet known for now, filled in later.
             0, 0,                                    //6: bfReserved1
             0, 0,                                    //8: bfReserved2
             54, 0, 0, 0,                             //10: bfOffBits (54 header bytes)
             40, 0, 0, 0,                             //14: biSize
             uint8_t(w & 255), uint8_t(w >> 8), 0, 0, //18: biWidth
             uint8_t(h & 255), uint8_t(h >> 8), 0, 0, //22: biHeight
             1, 0,                                    //26: biPlanes
             24, 0,                                   //28: biBitCount
             0, 0, 0, 0,                              //30: biCompression
             0, 0, 0, 0,                              //34: biSizeImage
             0, 0, 0, 0,                              //38: biXPelsPerMeter
             0, 0, 0, 0,                              //42: biYPelsPerMeter
             0, 0, 0, 0,                              //46: biClrUsed
             0, 0, 0, 0 };                            //50: biClrImportant

    /*
    Convert the input RGBRGBRGB pixel buffer to the BMP pixel buffer format. There are 3 differences with the input buffer:
    -BMP stores the rows inversed, from bottom to top
    -BMP stores the color channels in BGR instead of RGB order
    -BMP requires each row to have a multiple of 4 bytes, so sometimes padding bytes are added between rows
    */
    int pix_in_line = w * 3;
    int imagerowbytes = (pix_in_line & 3) == 0 ? pix_in_line : 4 + (pix_in_line & ~3); //must be multiple of 4

    for (int y = h * pix_in_line; y >= pix_in_line; y -= pix_in_line) //the rows are stored inversed in bmp
    {
        for (int x = y - pix_in_line; x < y; x += 3)
        {
            bmp.push_back(image[x + 2]);
            bmp.push_back(image[x + 1]);
            bmp.push_back(image[x]);
        }
        for (int x = pix_in_line; x < imagerowbytes; ++x)
        {
            bmp.push_back(0);
        }
    }

    // Fill in the size
    bmp[2] = bmp.size() & 255;
    bmp[3] = bmp.size() >> 8 & 255;
    bmp[4] = bmp.size() >> 16 & 255;
    bmp[5] = bmp.size() >> 24 & 255;
}

void ImageDraw::PngToBmp(const std::wstring& filename)
{
    std::vector<unsigned char> image; //the raw pixels
    unsigned int width, height;
    std::string infile = Encoding::wstring_to_utf8(filename);

    unsigned int error = lodepng::decode(image, width, height, infile, LCT_RGB, 8);
    if (error)
    {
        return ;
    }

    std::vector<uint8_t> bmp;
    encodeBMP(bmp, &image[0], width, height);
    infile.replace(infile.rfind('.') + 1, 3, "bmp");
    lodepng::save_file(bmp, infile);
}