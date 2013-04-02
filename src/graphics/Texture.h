//
//  Texture.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_GRAPHICS_TEXTURE_H_
#define DRY_GRAPHICS_TEXTURE_H_

namespace dry {

class Texture
{
public:
    struct Params
    {
        Params()
        {
            Bilinear = true;
            Mipmaps  = false;
            FlipY    = false;
        }
        Params(bool bilinear, bool mipmaps, bool flipy)
        {
            Bilinear = bilinear;
            Mipmaps  = mipmaps;
            FlipY    = flipy;
        }
        bool    Bilinear;
        bool    Mipmaps;
        bool    FlipY;
    };
public:
                Texture         () { m_Handle = 0; }
               ~Texture         () { Free(); }

    bool        InitWithData    (int width, int height, PixelFormat format, Params const &params, void const *data);
    bool        InitWithHandle  (int width, int height, PixelFormat format, int handle);
    void        Free            ();

    void        Update          (void const *data);

    void        Bind            (int stage);
    void        Unbind          ();
    
private:
    
    int         GetGLFormat     ();
    int         GetGLType       ();
    
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

#endif
