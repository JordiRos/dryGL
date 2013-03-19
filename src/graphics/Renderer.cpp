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
// Init
//
//------------------------------------------------------------------------------------------------
void Renderer::Init()
{
    m_BlendMode = BLEND_UNKNOWN;
    SetBlendMode(BLEND_ALPHA);
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
void Renderer::Clear(int bits, Colorf const &color, float depth, int stencil)
{
    if (bits & GL_COLOR_BUFFER_BIT)
        glClearColor(color.r, color.g, color.b, color.a);
    if (bits & GL_DEPTH_BUFFER_BIT)
        glClearDepthf(depth);
    if (bits & GL_STENCIL_BUFFER_BIT)
        glClearStencil(stencil);
    // Clear
    glClear(bits);
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

