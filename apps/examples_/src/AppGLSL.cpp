//
//  AppGLSL.cpp
//  dryExamples
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "AppGLSL.h"
#include "QuadBatch.h"
#include "ImageLoader.h"


static dry::CameraOrthogonal _camera;
static dry::Shader _shader;
static dry::QuadBatch _quads;


//------------------------------------------------------------------------------------------------
// Constructor
//
//------------------------------------------------------------------------------------------------
AppGLSL::AppGLSL(dry::AppParams const &params) : dry::AppiOS(params)
{
    // Shader
    _shader.InitWithFile(dry::GetFilePath("glsl.vs"), dry::GetFilePath("glsl_lights.fs"));
    
    // Camera
    int w = GetParams().Width;
    int h = GetParams().Height;

    // Orthogonal
    _camera.Init(0,w, 0,h, -1.f,1.f);
    _camera.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    // QuadBatch
    _quads.Init();
    
    // Viewport
    GetRenderer()->SetViewport(0,0, w,h);
}


//------------------------------------------------------------------------------------------------
// Update
//
//------------------------------------------------------------------------------------------------
void AppGLSL::Update(float time, float delta)
{
}


//------------------------------------------------------------------------------------------------
// Draw
//
//------------------------------------------------------------------------------------------------
void AppGLSL::Draw()
{
    GetRenderer()->Clear(true, true, false);
    GetRenderer()->SetBlendMode(dry::BLEND_ALPHA);

    int w = GetParams().Width;
    int h = GetParams().Height;

    // Draw quad with GLSL shader
    _shader.Bind();
    glUniform1f(_shader.GetUniformLocation("time"), GetTimer().GetTime());
    _quads.DrawShader(&_shader, &_camera, glm::mat4(), 0.f,0.f, w,h);
    _shader.Unbind();
}
