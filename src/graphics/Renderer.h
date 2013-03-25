//
//  Renderer.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class Renderer
{
public:
                    Renderer        (int w, int h, bool depth, bool stencil);
                   ~Renderer        ();

    void            Begin           ();
    void            End             ();

    void            Clear           (bool color, bool depth, bool stencil);
    
    void            DrawArrays      (int mode, int count);
    void            DrawElements    (int mode, int count, int type);
    
    void            SetViewport     (int x, int y, int w, int h);
    void            SetClearColor   (glm::vec4 const &color, float depth, int stencil);
    void            SetBlendMode    (BlendMode blend);

    uint            GetColorBuffer  () { return m_ColorRenderBuffer; }
    uint            GetDepthBuffer  () { return m_DepthRenderBuffer; }
    uint            GetFrameBuffer  () { return m_FrameBuffer; }

private:
    
    uint            m_ColorRenderBuffer;
    uint            m_DepthRenderBuffer;
    uint            m_FrameBuffer;
    glm::vec4       m_ClearColor;
    float           m_ClearDepth;
    float           m_ClearStencil;
    BlendMode       m_BlendMode;
};

}
