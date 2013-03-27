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

dry::CameraOrthogonal  CameraO;
dry::CameraPerspective CameraP;
dry::ShaderBasic       Shader;
dry::Shader            ShaderDot;
dry::QuadBatch         QuadBatch;
dry::Texture           Texture;
dry::Fbo               Fbo;
// Uniforms
dry::Uniform           UModelViewProjection;
dry::Uniform           UTexture;
dry::Uniform           UCenter;
dry::Uniform           UAngle;
dry::Uniform           UScale;
dry::Uniform           USize;

#define STRINGIFY(A) #A
string VS = STRINGIFY(
    precision mediump float;

    attribute vec3 Position;
    attribute vec2 TexCoord;
    uniform mat4 ModelViewProjection;

    varying vec2 vUv;

    void main()
    {
        vUv = TexCoord;
        gl_Position = ModelViewProjection * vec4(Position, 1.0);
    }
);

string FS = STRINGIFY(
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

AppPostprocess(dry::AppParams const &params) : dry::AppiOS(params) { }

void OnInit()
{
    CameraO.Init(0.f,1.f, 0.f,1.f, 0.1f,1000.f);
    CameraO.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    CameraP.Init(45.f, (float)GetParams().Width / GetParams().Height, 0.1f, 10000.f);
    CameraP.LookAt(glm::vec3(0.0, 2.0, -2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    
    QuadBatch.Init(GetRenderer());
    Shader.Init();
    ShaderDot.InitWithProgram(VS, FS);
    dry::ImageLoader::LoadTexture(Texture, dry::GetFilePath("grid.jpg"), dry::Texture::Params(false, false));
    Fbo.Init(GetRenderer(), dry::Fbo::Params(GetParams().Width/4,GetParams().Height/4));
    
    // Uniforms
    UModelViewProjection.Init(ShaderDot.GetUniformLocation("ModelViewProjection"), dry::DataTypeMat4);
    UTexture.Init(ShaderDot.GetUniformLocation("texture"), dry::DataTypeFboColor);
    UCenter.Init(ShaderDot.GetUniformLocation("center"), dry::DataTypeVec2);
    UAngle.Init(ShaderDot.GetUniformLocation("angle"), dry::DataTypeFloat);
    UScale.Init(ShaderDot.GetUniformLocation("scale"), dry::DataTypeFloat);
    USize.Init(ShaderDot.GetUniformLocation("size"), dry::DataTypeVec2);
    
    // Init uniforms
    UTexture.Update(&Fbo, 0);
    UCenter.Update(glm::vec2(0.5f, 0.5f));
    UAngle.Update(1.57f);
    UScale.Update(1.0f);
    USize.Update(glm::vec2(GetParams().Width / 4, GetParams().Height / 4));

    GetRenderer()->SetClearColor(glm::vec4(0.f, 0.f, 0.f, 0.f), 0.f, 0);
}

void OnDraw()
{
    GetRenderer()->Clear(true, true, false);
    glDisable(GL_DEPTH_TEST);

    float angle = GetTimer().GetTime() * 45.f;
    glm::mat4 anim = glm::rotate(angle, glm::vec3(0, 1, 0));

    Fbo.Bind();
    GetRenderer()->Clear(true, true, false);
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

};
