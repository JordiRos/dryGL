//
//  Fbo.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_GRAPHICS_FBO_H_
#define DRY_GRAPHICS_FBO_H_

namespace dry {

class Fbo
{
public:
    struct Params
    {
        Params() { }
        Params(int width, int height) { Width = width; Height = height; }
        int     Width;
        int     Height;
    };
    
public:
                Fbo             () { m_Fbo = m_FboColor = m_FboDepth = 0; m_Renderer = NULL; }
               ~Fbo             () { Free(); }
    
    bool        Init            (Renderer * renderer, Params const &params);
    void        Free            ();
    
    void        Bind            ();
    void        Unbind          ();

    Texture    *GetTextureColor () { return &m_TextureColor; }
    Texture    *GetTextureDepth () { return &m_TextureDepth; }
    
private:
    
    Renderer   *m_Renderer;
    Params      m_Params;
    int         m_Target;
    int         m_Fbo;
    int         m_FboColor;
    int         m_FboDepth;
    int         m_FboDefault;
    Texture     m_TextureColor;
    Texture     m_TextureDepth;
    glm::ivec4  m_ViewportDefault;
};
    
}

#endif
