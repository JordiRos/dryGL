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
Renderer::Renderer()
{
    m_ClearColor   = Colorf(81.f / 255.f, 142.f / 255.f, 149.f / 255.f, 1.0f);
    m_ClearDepth   = 1.f;
    m_ClearStencil = 0;
    m_BlendMode    = BLEND_UNKNOWN;
}


//------------------------------------------------------------------------------------------------
// Begin
//
//------------------------------------------------------------------------------------------------
void Renderer::Begin()
{
}


//------------------------------------------------------------------------------------------------
// End
//
//------------------------------------------------------------------------------------------------
void Renderer::End()
{
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
void Renderer::SetClearColor(Colorf const &color, float depth, int stencil)
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
    glEnable(GL_BLEND);
    switch (m_BlendMode)
    {
        case BLEND_ALPHA:    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
        case BLEND_ADD:      glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
        case BLEND_PMALPHA:  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); break;
        case BLEND_PMADD:    glBlendFunc(GL_ONE, GL_ONE); break;
        case BLEND_SCREEN:   glBlendFunc(GL_ONE, GL_ONE); break;
        case BLEND_MULTIPLY: glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA); break;
        case BLEND_UNKNOWN:  return;
    }
    m_BlendMode = blend;
}

