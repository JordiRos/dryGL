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
    "attribute vec3 Position;"
    "uniform mat4 ModelViewProjection;"

    "void main(void)"
    "{"
        "gl_Position = ModelViewProjection * vec4(Position, 1.0);"
    "}";

static const char *s_FS =
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
