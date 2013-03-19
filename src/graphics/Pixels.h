//
//  Pixels.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class Pixels
{
public:
                Pixels              () { m_Data = NULL; }
               ~Pixels              () { Free(); }

    bool        InitWithFile        (const string &file);
    void        Free                ();
    void        Update              (const void *data);

    int         GetWidth            () const { return m_Width;  }
    int         GetHeight           () const { return m_Height; }
    PixelFormat GetFormat           () const { return m_Format; }
    uchar      *GetData             () const { return m_Data;   }
    int         GetBPP              () const;

private:
    
    bool        Init                (int width, int height, PixelFormat format);
    PixelFormat GetFormat           (int bpp) const;

private:
    
    int         m_Width;
    int         m_Height;
    PixelFormat m_Format;
    uchar      *m_Data;
};

}