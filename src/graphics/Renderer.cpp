//
//  Renderer.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Renderer.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Constructor
//
//------------------------------------------------------------------------------------------------
Renderer::Renderer(int w, int h, bool depth, bool stencil)
{
    // Vars
    m_ClearColor   = glm::vec4(80.f / 255.f, 130.f / 255.f, 200.f / 255.f, 1.0f);
    m_ClearDepth   = 1.f;
    m_ClearStencil = 0;
    m_BlendMode    = BlendUnknown;

    // RenderBuffer
    glGenRenderbuffers(1, &m_ColorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_ColorRenderBuffer);
    
    // DepthBuffer/StencilBuffer
    glGenRenderbuffers(1, &m_DepthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, w,h);
    
    // FrameBuffer
    glGenFramebuffers(1, &m_FrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_ColorRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_RENDERBUFFER, m_DepthRenderBuffer);
    
    // Default gl states
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    // Default render states
    SetBlendMode(dry::BlendAlpha);
    SetViewport (0, 0, w, h);
}


//------------------------------------------------------------------------------------------------
// Renderer
//
//------------------------------------------------------------------------------------------------
Renderer::~Renderer()
{
    
}


//------------------------------------------------------------------------------------------------
// Begin
//
//------------------------------------------------------------------------------------------------
void Renderer::Begin()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
}


//------------------------------------------------------------------------------------------------
// End
//
//------------------------------------------------------------------------------------------------
void Renderer::End()
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_ColorRenderBuffer);
}


//------------------------------------------------------------------------------------------------
// Clear
//
//------------------------------------------------------------------------------------------------
void Renderer::Clear(bool color, bool depth, bool stencil)
{
    glClearColor  (m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, m_ClearColor.a);
    glClearDepthf (m_ClearDepth);
    glClearStencil(m_ClearStencil);
    // Clear
    int bits = (color ? GL_COLOR_BUFFER_BIT : 0) | (depth ? GL_DEPTH_BUFFER_BIT : 0) | (stencil ? GL_STENCIL_BUFFER_BIT : 0);
    glClear(bits);
}


//------------------------------------------------------------------------------------------------
// SetViewport
//
//------------------------------------------------------------------------------------------------
void Renderer::SetViewport(int x, int y, int w, int h)
{
    glViewport(x, y, w, h);
}


//------------------------------------------------------------------------------------------------
// SetClearColor
//
//------------------------------------------------------------------------------------------------
void Renderer::SetClearColor(glm::vec4 const &color, float depth, int stencil)
{
    m_ClearColor = color;
    m_ClearDepth = depth;
    m_ClearStencil = stencil;
}


//------------------------------------------------------------------------------------------------
// SetBlendMode
//
//------------------------------------------------------------------------------------------------
void Renderer::SetBlendMode(BlendMode blend)
{
    switch (blend)
    {
        case BlendAlpha:    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
        case BlendAdd:      glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
        case BlendPMAlpha:  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); break;
        case BlendPMAdd:    glBlendFunc(GL_ONE, GL_ONE); break;
        case BlendScreen:   glBlendFunc(GL_ONE, GL_ONE); break;
        case BlendMultiply: glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA); break;
        default: return;
    }
    m_BlendMode = blend;
}


//------------------------------------------------------------------------------------------------
// DrawArrays
//
//------------------------------------------------------------------------------------------------
void Renderer::DrawArrays(int mode, int count)
{
    glDrawArrays(mode, 0, count);
}


//------------------------------------------------------------------------------------------------
// DrawElements
//
//------------------------------------------------------------------------------------------------
void Renderer::DrawElements(int mode, int count, int type)
{
    glDrawElements(mode, count, type, 0);
}
