//
//  AppParticles.h
//
//  Example: Screen space GLSL shader example
//

#pragma once

#include "dry.h"
#include "QuadBatch.h"

class AppParticles : public dry::AppiOS
{
public:
    
    const char *VS = STRING(
        precision mediump float;
                            
        attribute vec3 Position;
        attribute vec2 Attribute;
        uniform float Time;
        uniform mat4 ModelViewProjection;
        varying vec3 vParticle;
                          
        void main(void)
        {
            gl_PointSize = cos(Time * Attribute.y + Attribute.x) * 6.0 + 8.0;
            gl_Position = ModelViewProjection * vec4(Position, 1.0);
            vParticle = vec3(gl_Position.xy, Time);
        }
    );

    const char *FS = STRING(
        precision mediump float;
    
        uniform sampler2D Texture;
                          
        varying vec3 vParticle;

        void main(void)
        {
            gl_FragColor = texture2D(Texture, gl_PointCoord);
        }
    );
    
    const int PARTICLES = 10000;

public:
    
    AppParticles(dry::AppParams const &params) : dry::AppiOS(params) { }

    //------------------------------------------------------------------------------------------------
    // OnInit
    //------------------------------------------------------------------------------------------------
    void OnInit()
    {
        int w = GetParams().Width;
        int h = GetParams().Height;
        
        Camera.Init(45.f, (float)w / h, 0.1, 1000.f);
        Camera.LookAt(glm::vec3(0.0, 0.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        QuadBatch.Init(m_Renderer);
        Shader.InitWithProgram(VS, FS);
        dry::ImageLoader::Load(Texture, dry::GetFilePath("particle.png"), dry::Texture::Params(false, false));

        // Uniforms
        UModelViewProjection.Init(&Shader, "ModelViewProjection", dry::DataTypeMat4);
        UTime.Init(&Shader, "Time", dry::DataTypeFloat);
        UTexture.Init(&Shader, "Texture", dry::DataTypeTex2D);
        UTexture.Update(&Texture, 0);
        
        // Attributes
        //Vertices.Init(Positions, PARTICLES, dry::DataTypeVec3, false);
        //VAttributes.Init(Attributes, PARTICLES, dry::DataTypeVec2, false);
        APositions.Init(&Shader, "Position", PARTICLES, dry::DataTypeVec3, false);
        AAttributes.Init(&Shader, "Attribute", PARTICLES, dry::DataTypeVec2, false);
        
        dry::Log(dry::LogInfo, "Initialize %d particles", PARTICLES);
        dry::Random random;
        Positions  = (glm::vec3 *)APositions.GetData();
        Attributes = (glm::vec2 *)AAttributes.GetData();
        for (int i = 0; i < PARTICLES; i++)
        {
            Positions[i].x = random.Next(-0.5f, 0.5f);
            Positions[i].y = random.Next(-0.5f, 0.5f);
            Positions[i].z = random.Next(-0.5f, 0.5f);
            Attributes[i].x = random.Next(0.f, (float)M_PI); // Offset
            Attributes[i].y = random.Next(5.f, 10.f);         // Speed
        }
        APositions.Update(true);
        AAttributes.Update(true);
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        m_Renderer->Clear(true, true, false);
        m_Renderer->SetBlendMode(dry::BlendPMAdd);
        glDisable(GL_DEPTH_TEST);
        
        Shader.Bind();

        float time = GetTimer().GetTime();
        // Matrices
        float angle = time * 45;
        glm::mat4 anim = glm::rotate(angle, glm::vec3(0, 1, 0));
        glm::mat4 model = glm::translate(glm::vec3(0.0, 0.0, 0.0));
        UModelViewProjection.Update(Camera.GetMatProjection() * Camera.GetMatView() * model * anim);
        UModelViewProjection.Bind();

        UTexture.Bind();
        UTime.Update(time);
        UTime.Bind();
        APositions.Bind();
        AAttributes.Bind();
        
        m_Renderer->DrawArrays(GL_POINTS, PARTICLES);
        
        Texture.Unbind();
        Shader.Unbind();
    }

private:

    dry::CameraPerspective  Camera;
    dry::QuadBatch          QuadBatch;
    dry::Shader             Shader;
    dry::Texture            Texture;
    dry::Attribute          APositions;
    dry::Attribute          AAttributes;
    dry::Uniform            UModelViewProjection;
    dry::Uniform            UTime;
    dry::Uniform            UTexture;
    glm::vec3              *Positions;
    glm::vec2              *Attributes;

};