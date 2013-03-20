//
//  Image.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Image.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// InitWithData
//
//------------------------------------------------------------------------------------------------
bool Image::InitWithData(int width, int height, PixelFormat format, const void *data)
{
    m_Width  = width;
    m_Height = height;
    m_Format = format;
    m_Data   = NEW_ARRAY(uchar, width * height * GetBPP());
    if (data)
        memcpy(m_Data, data, width * height * GetBPP());
    return true;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Image::Free()
{
    DISPOSE_ARRAY(m_Data);
}


//------------------------------------------------------------------------------------------------
// GetBPP
//
//------------------------------------------------------------------------------------------------
int Image::GetBPP() const
{
    switch (m_Format)
    {
        case PF_ALPHA:   return 1;
        case PF_RGB565:  return 2;
        case PF_RGB24:   return 3;
        case PF_ARGB32:  return 4;
        case PF_UNKNOWN: return 0;
    }
    return 0;
}


//------------------------------------------------------------------------------------------------
// GetFormat
//
//------------------------------------------------------------------------------------------------
PixelFormat Image::GetFormat(int bpp) const
{
    switch (bpp)
    {
        case 1: return PF_ALPHA;
        case 2: return PF_RGB565;
        case 3: return PF_RGB24;
        case 4: return PF_ARGB32;
    }
    return PF_UNKNOWN;
}
