//
//  AppPostprocess.h
//
//  Example: Screen space GLSL shader example
//

#pragma once

#include "dry.h"
#include "QuadBatch.h"

class AppPostprocess : public dry::App
{
public:
    
    // VertexShader
    const char *vertexShader = STRING(
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
    const char *fragmentShader = STRING(
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
    
    AppPostprocess(dry::AppParams const &params) : dry::App(params) { }

    //------------------------------------------------------------------------------------------------
    // OnInit
    //------------------------------------------------------------------------------------------------
    void OnInit()
    {
        cameraO.Init(0.f,1.f, 0.f,1.f, 0.1f,1000.f);
        cameraO.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        cameraP.Init(45.f, (float)GetParams().Width / GetParams().Height, 0.1f, 10000.f);
        cameraP.LookAt(glm::vec3(0.0, 1.0, -3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        
        quadBatch.Init(m_Renderer);
        shaderDot.Init(vertexShader, fragmentShader);
        dry::ImageUtils::Load(texture, dry::GetFilePath("grid.jpg"), dry::Texture::Params(false, false, false));
        fbo.Init(m_Renderer, dry::Fbo::Params(GetParams().Width/4,GetParams().Height/4));
        
        // Uniforms
        uModelViewProjection = shaderDot.GetUniformByName("ModelViewProjection");
        uTexture = shaderDot.GetUniformByName("texture");
        uCenter  = shaderDot.GetUniformByName("center");
        uAngle   = shaderDot.GetUniformByName("angle");
        uScale   = shaderDot.GetUniformByName("scale");
        uSize    = shaderDot.GetUniformByName("size");
        
        // Init uniforms
        uTexture->Update(0);
        uCenter ->Update(glm::vec2(0.5f, 0.5f));
        uAngle  ->Update(1.57f);
        uScale  ->Update(1.0f);
        uSize   ->Update(glm::vec2(GetParams().Width / 4, GetParams().Height / 4));
        
        m_Renderer->SetClearColor(glm::vec4(0.f, 0.f, 0.f, 0.f), 0.f, 0);
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        m_Renderer->Clear(true, false, false);
        glDisable(GL_DEPTH_TEST);

        float angle = GetTimer().GetTime() * 45.f;
        glm::mat4 anim = glm::rotate(angle, glm::vec3(0, 1, 0));

        texture.Bind(0);
        fbo.Bind();
        m_Renderer->Clear(true, false, false);
        quadBatch.DrawTexture(&texture, &cameraP, anim, -0.5,-0.5, 1.f,1.f);
        fbo.Unbind();

        // Postprocess: ShaderDot
        fbo.GetTextureColor()->Bind(0);
        quadBatch.DrawShader(&shaderDot, &cameraO, glm::mat4(), 0.f, 0.f, 1.f, 1.f);
    }

private:
    
    dry::CameraOrthogonal   cameraO;
    dry::CameraPerspective  cameraP;
    dry::Shader             shaderDot;
    dry::QuadBatch          quadBatch;
    dry::Texture            texture;
    dry::Fbo                fbo;
    // Uniforms
    dry::Uniform           *uModelViewProjection;
    dry::Uniform           *uTexture;
    dry::Uniform           *uCenter;
    dry::Uniform           *uAngle;
    dry::Uniform           *uScale;
    dry::Uniform           *uSize;
};
