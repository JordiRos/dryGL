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
bool Pixels::Init(int width, int height, int format)
{
    m_Width  = width;
    m_Height = height;
    m_Format = format;
    m_Data   = (void *)NEW_ARRAY(uchar, width * height * GetBPP());
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
            int bpp    = FreeImage_GetBPP   (fibmp);
            int format = GetFormat(bpp);
            if (format != -1)
            {
                if (Init(width, height, format))
                {
                    uchar *dst = (uchar *)m_Data;
                    for (int i = 0; i < height; i++)
                        memcpy(dst, FreeImage_GetScanLine(fibmp, i), bpp * width);
                    res = true;
                }
            }
            else
                dry::Log("[dryPixels] Unsupported format in image: BPP = %d", bpp);
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
        case DRY_FMT_ALPHA:  return 1;
        case DRY_FMT_RGB24:  return 3;
        case DRY_FMT_RGBA32: return 4;
    }
    return -1;
}


//------------------------------------------------------------------------------------------------
// GetFormat
//
//------------------------------------------------------------------------------------------------
int Pixels::GetFormat(int bpp) const
{
    switch (bpp)
    {
        case 1: return DRY_FMT_ALPHA;
        case 3: return DRY_FMT_RGB24;
        case 4: return DRY_FMT_RGBA32;
    }
    return -1;
}
