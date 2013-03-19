//
//  Pixels.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Pixels.h"
#include "freeimage/include/freeimage.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Pixels::Init(int width, int height, PixelFormat format)
{
    m_Width  = width;
    m_Height = height;
    m_Format = format;
    m_Data   = NEW_ARRAY(uchar, width * height * GetBPP());
    return true;
}


//------------------------------------------------------------------------------------------------
// InitWithFile
//
//------------------------------------------------------------------------------------------------
bool Pixels::InitWithFile(const string &file)
{
    bool res = false;
    FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(file.c_str(), 0);
    if (fif == FIF_UNKNOWN)
        fif = FreeImage_GetFIFFromFilename(file.c_str());
    if ((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif))
    {
        FIBITMAP *fibmp = FreeImage_Load(fif, file.c_str(), 0);
        if (fibmp)
        {
            int width  = FreeImage_GetWidth (fibmp);
            int height = FreeImage_GetHeight(fibmp);
            int bpp    = FreeImage_GetBPP   (fibmp) / 8;
            PixelFormat format = GetFormat(bpp);
            if (format != -1)
            {
                if (Init(width, height, format))
                {
                    uchar *src  = FreeImage_GetBits(fibmp);
                    uchar *dst  = m_Data;
                    int i, size = width * height;
                    switch (bpp)
                    {
                        case 1: memcpy(dst, src, bpp * width * height); break;
                        case 3:
                            for (i = 0; i < size; i++)
                            {
                                dst[0] = src[2];
                                dst[1] = src[1];
                                dst[2] = src[0];
                                src+= 3;
                                dst+= 3;
                            }
                            break;
                    }
                    res = true;
                }
            }
            else
                dry::Log(LOG_WARNING, "[dryPixels] Unsupported format in image: BPP = %d", bpp);
            FreeImage_Unload(fibmp);
        }
    }
    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Pixels::Free()
{
    DISPOSE_ARRAY(m_Data);
}


//------------------------------------------------------------------------------------------------
// GetBPP
//
//------------------------------------------------------------------------------------------------
int Pixels::GetBPP() const
{
    switch (m_Format)
    {
        case PF_ALPHA:   return 1;
        case PF_RGB565:  return 2;
        case PF_RGB24:   return 3;
        case PF_RGBA32:  return 4;
        case PF_UNKNOWN: return 0;
    }
    return 0;
}


//------------------------------------------------------------------------------------------------
// GetFormat
//
//------------------------------------------------------------------------------------------------
PixelFormat Pixels::GetFormat(int bpp) const
{
    switch (bpp)
    {
        case 1: return PF_ALPHA;
        case 3: return PF_RGB24;
        case 4: return PF_RGBA32;
    }
    return PF_UNKNOWN;
}
