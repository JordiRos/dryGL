//
//  AppParticles.h
//
//  Example: Screen space GLSL shader example
//

#ifndef APP_PARTICLES_H_
#define APP_PARTICLES_H_

#include "dry.h"
#include "QuadBatch.h"

class AppParticles : public dry::AppiOS
{
public:
    
    const char *vertexShader = STRING(
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

    const char *fragmentShader = STRING(
        precision mediump float;
    
        uniform sampler2D Texture;
                          
        varying vec3 vParticle;

        void main(void)
        {
            gl_FragColor = texture2D(Texture, gl_PointCoord);
        }
    );
    
    static const int PARTICLES = 10000;

public:
    
    AppParticles(dry::AppParams const &params) : dry::AppiOS(params) { }

    //------------------------------------------------------------------------------------------------
    // OnInit
    //------------------------------------------------------------------------------------------------
    void OnInit()
    {
        int w = GetParams().Width;
        int h = GetParams().Height;
        
        camera.Init(45.f, (float)w / h, 0.1, 1000.f);
        camera.LookAt(glm::vec3(0.0, 0.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        quadBatch.Init(m_Renderer);
        shader.Init(vertexShader, fragmentShader);
        dry::ImageUtils::Load(texture, dry::GetFilePath("particle.png"), dry::Texture::Params(false, false, false));

        // Uniforms
        uModelViewProjection = shader.GetUniformByName("ModelViewProjection");
        uTime = shader.GetUniformByName("Time");
        uTexture = shader.GetUniformByName("Texture");
        uTexture->Update(0);
        
        // Data
        dry::Log(dry::LogInfo, "Initialize %d particles", PARTICLES);
        dry::Random random;
        for (int i = 0; i < PARTICLES; i++)
        {
            vPos[i].x = random.Next(-0.5f, 0.5f);
            vPos[i].y = random.Next(-0.5f, 0.5f);
            vPos[i].z = random.Next(-0.5f, 0.5f);
            vAtt[i].x = random.Next(0.f, (float)M_PI); // Offset
            vAtt[i].y = random.Next(5.f, 10.f);         // Speed
        }
        // Vbos
        positions.Init(vPos, PARTICLES, dry::DataTypeVec3, false);
        attributes.Init(vAtt, PARTICLES, dry::DataTypeVec2, false);
        
        shader.GetAttribByName("Position")->SetVbo(&positions);
        shader.GetAttribByName("Attribute")->SetVbo(&attributes);
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        m_Renderer->Clear(true, true, false);
        m_Renderer->SetBlendMode(dry::BlendPMAdd);
        glDisable(GL_DEPTH_TEST);
        
        // Update
        float time = GetTimer().GetTime();
        float angle = time * 45;
        glm::mat4 anim = glm::rotate(angle, glm::vec3(0, 1, 0));
        glm::mat4 model = glm::translate(glm::vec3(0.0, 0.0, 0.0));
        uModelViewProjection->Update(camera.GetProjection() * camera.GetView() * model * anim);
        uTime->Update(time);
        
        // Bind
        texture.Bind(0);
        shader.Bind();
        
        m_Renderer->DrawArrays(GL_POINTS, PARTICLES);
        
        shader.Unbind();
        texture.Unbind();
    }

private:

    dry::CameraPerspective  camera;
    dry::QuadBatch          quadBatch;
    dry::Shader             shader;
    dry::Texture            texture;
    dry::Vbo                positions;
    dry::Vbo                attributes;
    dry::Uniform           *uModelViewProjection;
    dry::Uniform           *uTime;
    dry::Uniform           *uTexture;
    glm::vec3               vPos[PARTICLES];
    glm::vec2               vAtt[PARTICLES];
};

#endif
