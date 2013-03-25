//
//  AppGLSL.h
//
//  Example: Screen space GLSL shader example
//

#pragma once

#include "dry.h"
#include "QuadBatch.h"

class AppGLSL : public dry::AppiOS
{
public:

dry::CameraOrthogonal Camera;
dry::Shader           Shader;
dry::QuadBatch        QuadBatch;
dry::Uniform          UTime;

AppGLSL(dry::AppParams const &params) : dry::AppiOS(params) { }

void Init()
{
    int w = GetParams().Width;
    int h = GetParams().Height;
    
    Camera.Init(0,w, 0,h, 0.1f,10000.f);
    Camera.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    QuadBatch.Init(GetRenderer());
    Shader.InitWithFile(dry::GetFilePath("glsl.vs"), dry::GetFilePath("glsl_lights.fs"));
    UTime.Init(Shader.GetUniformLocation("time"), dry::UniformTypeFloat);
}

void Draw()
{
    GetRenderer()->Clear(true, true, false);
    
    int w = GetParams().Width;
    int h = GetParams().Height;
    
    Shader.Bind();
    UTime.Value = GetTimer().GetTime();
    UTime.Bind();
    QuadBatch.DrawShader(&Shader, &Camera, glm::mat4(), 0.f,0.f, w,h);
    Shader.Unbind();
}

};
