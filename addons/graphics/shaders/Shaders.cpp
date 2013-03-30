//
//  Shaders.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Shaders.h"


//------------------------------------------------------------------------------------------------
// Texture2D
//------------------------------------------------------------------------------------------------
const char *dry::Shaders::Texture2D_VS = STRING
(
    precision mediump float;

    attribute vec3 Position;
    attribute vec2 TexCoord;
    uniform mat4 Model;
    uniform mat4 View;
    uniform mat4 Projection;
    varying vec2 vUv;

    void main(void)
    {
        gl_Position = Projection * View * Model * vec4(Position, 1.0);
        vUv = TexCoord;
    }
);

const char *dry::Shaders::Texture2D_FS = STRING
(
    precision mediump float;

    uniform sampler2D Texture;
    varying vec2 vUv;

    void main(void)
    {
        gl_FragColor = texture2D(Texture, vUv);
    }
);
