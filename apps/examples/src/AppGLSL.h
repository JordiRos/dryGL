//
//  AppGLSL.h
//  dryExamples
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "AppGLSL.h"
#include "QuadBatch.h"
#include "ImageLoader.h"


class AppGLSL : public dry::AppiOS
{
public:

dry::CameraOrthogonal Camera;
dry::Shader           Shader;
dry::QuadBatch        QuadBatch;

    
AppGLSL(dry::AppParams const &params) : dry::AppiOS(params)
{
    int w = GetParams().Width;
    int h = GetParams().Height;
    
    Shader.InitWithFile(dry::GetFilePath("glsl.vs"), dry::GetFilePath("glsl_lights.fs"));
    Camera.Init(0,w, 0,h, -1.f,1.f);
    Camera.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    QuadBatch.Init();
    
    GetRenderer()->SetViewport(0,0, w,h);
}


void Draw()
{
    GetRenderer()->Clear(true, true, false);
    GetRenderer()->SetBlendMode(dry::BLEND_ALPHA);
    glDisable(GL_DEPTH_TEST);
    
    int w = GetParams().Width;
    int h = GetParams().Height;
    
    Shader.Bind();
    glUniform1f(Shader.GetUniformLocation("time"), GetTimer().GetTime());
    QuadBatch.DrawShader(&Shader, &Camera, glm::mat4(), 0.f,0.f, w,h);
    Shader.Unbind();
}


};
