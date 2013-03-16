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
