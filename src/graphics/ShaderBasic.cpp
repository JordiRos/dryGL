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
    "precision mediump float;"

    "attribute vec3 Position;"
    "attribute vec2 TexCoord;"
    "uniform mat4 ModelViewProjection;"
    "varying vec2 vUv;"

    "void main(void)"
    "{"
        "gl_Position = ModelViewProjection * vec4(Position, 1.0);"
        "vUv = TexCoord;"
    "}";

static const char *s_FS =
    "precision mediump float;"

    "uniform sampler2D Texture;"
    "varying vec2 vUv;"

    "void main(void)"
    "{"
        "gl_FragColor = texture2D(Texture, vUv);"
    "}";


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool ShaderBasic::Init()
{
    Free();
    bool res = false;
    if (InitWithProgram(s_VS, s_FS))
        res = true;
    else
        Free();
    return res;
}
