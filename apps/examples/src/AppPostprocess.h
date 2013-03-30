//
//  AppPostprocess.h
//
//  Example: Screen space GLSL shader example
//

#pragma once

#include "dry.h"
#include "QuadBatch.h"

class AppPostprocess : public dry::AppiOS
{
public:
    
    // VertexShader
    const char *VS = STRING(
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

    // FragmentShader
    const char *FS = STRING(
        precision mediump float;

        uniform vec2 center;
        uniform float angle;
        uniform float scale;
        uniform vec2 size;
        uniform sampler2D texture;

        varying vec2 vUv;

        float pattern()
        {
            float s = sin( angle );
            float c = cos( angle );
            vec2 tex = vUv * size - center;
            vec2 point = vec2( c * tex.x - s * tex.y, s * tex.x + c * tex.y ) * scale;
            return ( sin( point.x ) * sin( point.y ) ) * 4.0;
        }

        void main()
        {
            vec4 color = texture2D( texture, vUv );
            float average = ( color.r + color.g + color.b ) / 3.0;
            gl_FragColor = vec4( vec3( average * 10.0 - 5.0 + pattern() ), 1.0 );
        }
    );

public:
    
    AppPostprocess(dry::AppParams const &params) : dry::AppiOS(params) { }

    //------------------------------------------------------------------------------------------------
    // OnInit
    //------------------------------------------------------------------------------------------------
    void OnInit()
    {
        CameraO.Init(0.f,1.f, 0.f,1.f, 0.1f,1000.f);
        CameraO.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        CameraP.Init(45.f, (float)GetParams().Width / GetParams().Height, 0.1f, 10000.f);
        CameraP.LookAt(glm::vec3(0.0, 2.0, -2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        
        QuadBatch.Init(m_Renderer);
        Shader.InitWithProgram(dry::Shaders::Texture2D_VS, dry::Shaders::Texture2D_FS);
        ShaderDot.InitWithProgram(VS, FS);
        dry::ImageUtils::Load(Texture, dry::GetFilePath("grid.jpg"), dry::Texture::Params(false, false, false));
        Fbo.Init(m_Renderer, dry::Fbo::Params(GetParams().Width/4,GetParams().Height/4));
        
        // Uniforms
        UModelViewProjection.Init(&ShaderDot, "ModelViewProjection", dry::DataTypeMat4);
        UTexture.Init(&ShaderDot, "texture", dry::DataTypeTex2D);
        UCenter.Init(&ShaderDot, "center", dry::DataTypeVec2);
        UAngle.Init(&ShaderDot, "angle", dry::DataTypeFloat);
        UScale.Init(&ShaderDot, "scale", dry::DataTypeFloat);
        USize.Init(&ShaderDot, "size", dry::DataTypeVec2);
        
        // Init uniforms
        UTexture.Update(Fbo.GetTextureColor(), 0);
        UCenter.Update(glm::vec2(0.5f, 0.5f));
        UAngle.Update(1.57f);
        UScale.Update(1.0f);
        USize.Update(glm::vec2(GetParams().Width / 4, GetParams().Height / 4));

        m_Renderer->SetClearColor(glm::vec4(0.f, 0.f, 0.f, 0.f), 0.f, 0);
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        m_Renderer->Clear(true, true, false);
        glDisable(GL_DEPTH_TEST);

        float angle = GetTimer().GetTime() * 45.f;
        glm::mat4 anim = glm::rotate(angle, glm::vec3(0, 1, 0));

        Fbo.Bind();
        m_Renderer->Clear(true, true, false);
        QuadBatch.DrawTexture(&Texture, &CameraP, anim, -0.5,-0.5, 1.f,1.f);
        Fbo.Unbind();

        // Postprocess: ShaderDot
        ShaderDot.Bind();
        UTexture.Bind();
        UCenter.Bind();
        UAngle.Bind();
        UScale.Bind();
        USize.Bind();
        
        QuadBatch.DrawShader(&ShaderDot, &CameraO, glm::mat4(), 0.f, 0.f, 1.f, 1.f);
        
        UTexture.Unbind();
    }

private:
    
    dry::CameraOrthogonal   CameraO;
    dry::CameraPerspective  CameraP;
    dry::Shader             Shader;
    dry::Shader             ShaderDot;
    dry::QuadBatch          QuadBatch;
    dry::Texture            Texture;
    dry::Fbo                Fbo;
    // Uniforms
    dry::Uniform            UModelViewProjection;
    dry::Uniform            UTexture;
    dry::Uniform            UCenter;
    dry::Uniform            UAngle;
    dry::Uniform            UScale;
    dry::Uniform            USize;
};
