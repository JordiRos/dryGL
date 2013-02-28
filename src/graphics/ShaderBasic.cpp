//
//  ShaderBasic.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Shader.h"
#include "ShaderBasic.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Program
//------------------------------------------------------------------------------------------------
static const char *s_VS =
    "attribute vec4 aPos;"
    "attribute vec4 aCol;"
    "attribute vec2 aTexCoord;"

    "uniform mat4 projection;"
    "uniform mat4 modelView;"

    "varying vec2 vTexCoord;"
    "varying vec4 vColor;"

    "void main(void)"
    "{"
        "vColor = aCol;"
        "vTexCoord = aTexCoord;"
        "gl_Position = projection * modelView * aPos;"
    "}";

static const char *s_FS =
    "varying lowp vec4 vColor;"
    "varying lowp vec2 vTexCoord;"

    "uniform sampler2D texture;"

    "void main(void)"
    "{"
        "gl_FragColor = vec4(1.0,1.0,1.0,1.0);"
    "}";


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool ShaderBasic::Init()
{
    Free();
    bool res = false;
    m_Shader = new Shader();
    if (m_Shader->InitWithProgram(s_VS, s_FS))
    {
        res = true;
    }
    else
        Free();
    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void ShaderBasic::Free()
{
    DISPOSE(m_Shader);
}


//------------------------------------------------------------------------------------------------
// Begin
//
//------------------------------------------------------------------------------------------------
void ShaderBasic::Begin()
{
    m_Shader->Begin();
}


//------------------------------------------------------------------------------------------------
// End
//
//------------------------------------------------------------------------------------------------
void ShaderBasic::End()
{
    m_Shader->End();
}
