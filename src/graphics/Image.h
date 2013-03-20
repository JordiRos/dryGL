//
//  Image.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class Image
{
public:
                Image               () { m_Data = NULL; }
               ~Image               () { Free(); }

    bool        InitWithData        (int width, int height, PixelFormat format, const void *data);
    void        Free                ();
    void        Update              (const void *data);

    int         GetWidth            () const { return m_Width;  }
    int         GetHeight           () const { return m_Height; }
    PixelFormat GetFormat           () const { return m_Format; }
    uchar      *GetData             () const { return m_Data;   }
    int         GetBPP              () const;

private:
    
    PixelFormat GetFormat           (int bpp) const;

private:
    
    int         m_Width;
    int         m_Height;
    PixelFormat m_Format;
    uchar      *m_Data;
};

}