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
bool Image::InitWithData(int width, int height, PixelFormat format, void const *data)
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
        case PixelFormatAlpha:   return 1;
        case PixelFormatRgb565:  return 2;
        case PixelFormatRgb24:   return 3;
        case PixelFormatArgb32:  return 4;
        default:                 return 0;
    }
}


//------------------------------------------------------------------------------------------------
// GetFormat
//
//------------------------------------------------------------------------------------------------
PixelFormat Image::GetFormat(int bpp) const
{
    switch (bpp)
    {
        case 1: return PixelFormatAlpha;
        case 2: return PixelFormatRgb565;
        case 3: return PixelFormatRgb24;
        case 4: return PixelFormatArgb32;
    }
    return PixelFormatUnknown;
}
