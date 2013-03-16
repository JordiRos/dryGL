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

    bool        InitWithData    (int width, int height, int format, int target, const void *data);
    bool        InitWithPixels  (const Pixels &pixels);
    void        Free            ();

    void        Update          (const void *data);

    void        Bind            (int uniform, int stage = 0) const;
    void        Unbind          () const;
    
private:
    
    bool        Init            (int width, int height, int format, int target);
    int         GetGLFormat     () const;
    int         GetGLType       () const;
    
private:
    
    int         m_Handle;
    int         m_Width;
    int         m_Height;
    int         m_Format;
    int         m_Target;
};

}