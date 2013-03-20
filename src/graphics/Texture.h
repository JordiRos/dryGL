//
//  Texture.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class Pixels;

class Texture
{
public:
                Texture         () { m_Handle = -1; }
               ~Texture         () { Free(); }

    bool        InitWithData    (int width, int height, PixelFormat format, const void *data);
    bool        InitWithImage   (const Image &img);
    void        Free            ();

    void        Update          (const void *data);

    void        Bind            (int uniform, int stage) const;
    void        Unbind          () const;
    
private:
    
    int         GetGLFormat     () const;
    int         GetGLType       () const;
    
private:
    
    int         m_Handle;
    int         m_Width;
    int         m_Height;
    PixelFormat m_Format;
    int         m_Target;
};

}