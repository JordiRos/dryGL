//
//  Renderer.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_GRAPHICS_RENDERER_H_
#define DRY_GRAPHICS_RENDERER_H_

namespace dry {
    
class Renderer
{
public:
                        Renderer        (int w, int h, bool depth, bool stencil);
                       ~Renderer        ();

    void                Begin           ();
    void                End             ();

    void                Clear           (bool color, bool depth, bool stencil);
    
    void                DrawArrays      (int mode, int count);
    void                DrawElements    (int mode, int count, int type);
    
    void                SetViewport     (int x, int y, int w, int h);
    void                SetClearColor   (glm::vec4 const &color, float depth, int stencil);
    void                SetBlendMode    (BlendMode blend);

    glm::ivec4 const   &GetViewport     () { return m_Viewport; }
    uint                GetColorBuffer  () { return m_ColorRenderBuffer; }
    uint                GetDepthBuffer  () { return m_DepthRenderBuffer; }
    uint                GetFrameBuffer  () { return m_FrameBuffer; }
    bool                GetRendering    () { return m_Rendering; }

private:
    
    glm::ivec4          m_Viewport;
    uint                m_ColorRenderBuffer;
    uint                m_DepthRenderBuffer;
    uint                m_FrameBuffer;
    glm::vec4           m_ClearColor;
    float               m_ClearDepth;
    float               m_ClearStencil;
    BlendMode           m_BlendMode;
    bool                m_Rendering;
};

}

#endif
