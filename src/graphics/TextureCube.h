//
//  TextureCube.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class TextureCube
{
public:
    struct Params
    {
        Params()
        {
            Bilinear = true;
            Mipmaps  = false;
        }
        Params(bool bilinear, bool mipmaps)
        {
            Bilinear = bilinear;
            Mipmaps  = mipmaps;
        }
        bool    Bilinear;
        bool    Mipmaps;
    };
    
public:
                TextureCube     () { m_Handle = -1; }
               ~TextureCube     () { Free(); }

    bool        InitWithData    (int width, int height, PixelFormat format, Params const &params, void const **data);
    bool        InitWithHandle  (int width, int height, PixelFormat format, int handle);
    void        Free            ();

    void        Update          (TextureCubeSide side, void const *data);

    void        Bind            (int stage) const;
    void        Unbind          () const;
    
private:
    
    int         GetGLFormat     () const;
    int         GetGLType       () const;
    
private:
    
    int         m_Handle;
    int         m_Width;
    int         m_Height;
    PixelFormat m_Format;
    Params      m_Params;
    int         m_Target;
    bool        m_Release;
};

}