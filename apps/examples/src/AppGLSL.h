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

void OnInit()
{
    Camera.Init(0,1, 0,1, 0.1f,10000.f);
    Camera.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    QuadBatch.Init(GetRenderer());
    Shader.InitWithFile(dry::GetFilePath("glsl.vs"), dry::GetFilePath("glsl_lights.fs"));
    UTime.Init(Shader.GetUniformLocation("time"), dry::DataTypeFloat);
}

void OnDraw()
{
    glDisable(GL_DEPTH_TEST);

    Shader.Bind();
    UTime.Update(GetTimer().GetTime());
    UTime.Bind();
    QuadBatch.DrawShader(&Shader, &Camera, glm::mat4(), 0.f,0.f, 1.f,1.f);
    Shader.Unbind();
}

};
