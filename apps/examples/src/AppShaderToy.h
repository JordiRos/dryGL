//
//  AppShaderToy.h
//
//  Example: Screen space GLSL viewer
//
//  You can directly load and view shaders from ShaderToy by Iñigo Quilez: http://www.shadertoy.com
//  * Some vars are missing
//  * It can take some seconds for some shaders to render a single frame... be patient
//

#pragma once

#include "dry.h"
#include "QuadBatch.h"

#define SAMPLES 6

class AppShaderToy : public dry::AppiOS
{
public:

    AppShaderToy(dry::AppParams const &params) : dry::AppiOS(params) { }

    //------------------------------------------------------------------------------------------------
    // OnInit
    //------------------------------------------------------------------------------------------------
    void OnInit()
    {
        Camera.Init(0,1, 0,1, 0.1f,1000.f);
        Camera.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        QuadBatch.Init(m_Renderer);
        dry::ShaderLoader::Load(Shader, dry::GetFilePath("glsl.vs"), dry::GetFilePath("glsl_cube.fs"));
        //dry::ImageLoader::Load(Texture, dry::GetFilePath("grid.jpg"), dry::Texture::Params(true, true));
        dry::ImageLoader::Load(TextureCube, dry::GetFilePath("cube02.jpg"), dry::TextureCube::Params(true, true));
        
        // Uniforms
        UResolution.Init(&Shader, "iResolution", dry::DataTypeVec3);
        UGlobalTime.Init(&Shader, "iGlobalTime", dry::DataTypeFloat);
        UMouse.Init(&Shader, "iMouse", dry::DataTypeVec4);
        UChannel0.Init(&Shader, "iChannel0", dry::DataTypeTexCube);
        
        // Uniform values
        UResolution.Update(glm::vec3(GetParams().Width / SAMPLES, GetParams().Height / SAMPLES, 0.f));
        UGlobalTime.Update(0.f);
        UMouse.Update(glm::vec4(0.f,0.f,0.f,0.f));
        UChannel0.Update(&TextureCube, 0);
        
        Fbo.Init(m_Renderer, dry::Fbo::Params(GetParams().Width / SAMPLES, GetParams().Height / SAMPLES));
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        glDisable(GL_DEPTH_TEST);

        Fbo.Bind();
        
        Shader.Bind();
        UResolution.Bind();
        UGlobalTime.Update(GetTime());
        UGlobalTime.Bind();
        UMouse.Bind();
        UChannel0.Bind();
        QuadBatch.DrawShader(&Shader, &Camera, glm::mat4(), 0.f,0.f, 1.f,1.f);
        UChannel0.Unbind();
        Shader.Unbind();

        Fbo.Unbind();
        
        QuadBatch.DrawTexture(Fbo.GetTextureColor(), &Camera, glm::mat4(), 0,0, 1.f,1.f);
    }

private:

    dry::CameraOrthogonal Camera;
    dry::Shader           Shader;
    dry::QuadBatch        QuadBatch;
    dry::Texture          Texture;
    dry::TextureCube      TextureCube;
    dry::Uniform          UResolution;
    dry::Uniform          UGlobalTime;
    dry::Uniform          UMouse;
    dry::Uniform          UChannel0;
    dry::Fbo              Fbo;
};
