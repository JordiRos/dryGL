//
//  MeshMaterialDiffuse.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "MeshMaterialDiffuse.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// VS
//------------------------------------------------------------------------------------------------
static const char *s_VS = STRING(
    precision mediump float;
                                     
    attribute vec3 Position;
    attribute vec2 TexCoord0;
    attribute vec3 Normal;
    attribute vec4 Color;
    uniform mat4 Model;
    uniform mat4 View;
    uniform mat4 Projection;
    varying vec2 vUv;
    varying vec4 vColor;

    void main(void)
    {
        gl_Position = Projection * View * Model * vec4(Position, 1.0);
        vUv = TexCoord0;
        vColor = Color;
    }
);


//------------------------------------------------------------------------------------------------
// FS
//------------------------------------------------------------------------------------------------
static const char *s_FS = STRING(
    precision mediump float;
                                     
    uniform sampler2D Texture0;
    varying vec2 vUv;
    varying vec4 vColor;

    void main(void)
    {
        gl_FragColor = texture2D(Texture0, vUv) * vColor;
    }
);


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool MeshMaterialDiffuse::Init()
{
    bool res = false;
    Free();
    
    if (MeshMaterial::Init(s_VS, s_FS))
        res = true;
    
    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void MeshMaterialDiffuse::Free()
{
    MeshMaterial::Free();
}
