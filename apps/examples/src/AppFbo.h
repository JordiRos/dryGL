//
//  AppFbo.h
//
//  Example: How to render to texture using Fbo and set that texture as source for another geometry
//

#ifndef APP_FBO_H_
#define APP_FBO_H_

#include "dry.h"
#include "QuadBatch.h"
#include "Shaders.h"

class AppFbo : public dry::AppiOS
{
public:
    
    AppFbo(dry::AppParams const &params) : dry::AppiOS(params) { }
        
    //------------------------------------------------------------------------------------------------
    // OnInit
    //------------------------------------------------------------------------------------------------
    void OnInit()
    {
        // Vertices
        GLfloat aVertices[] = {
            // front
            -1.0, -1.0,  1.0,
            1.0, -1.0,  1.0,
            1.0,  1.0,  1.0,
            -1.0,  1.0,  1.0,
            // top
            -1.0,  1.0,  1.0,
            1.0,  1.0,  1.0,
            1.0,  1.0, -1.0,
            -1.0,  1.0, -1.0,
            // back
            1.0, -1.0, -1.0,
            -1.0, -1.0, -1.0,
            -1.0,  1.0, -1.0,
            1.0,  1.0, -1.0,
            // bottom
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0, -1.0,  1.0,
            -1.0, -1.0,  1.0,
            // left
            -1.0, -1.0, -1.0,
            -1.0, -1.0,  1.0,
            -1.0,  1.0,  1.0,
            -1.0,  1.0, -1.0,
            // right
            1.0, -1.0,  1.0,
            1.0, -1.0, -1.0,
            1.0,  1.0, -1.0,
            1.0,  1.0,  1.0,
        };
        // TexCoords
        GLfloat aTexcoords[2*4*6] = {
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0,
        };
        for (int i = 1; i < 6; i++)
            memcpy(&aTexcoords[i*4*2], &aTexcoords[0], 2*4*sizeof(GLfloat));
        // Indices
        GLushort aIndices[] = {
            // front
            0,  1,  2,
            2,  3,  0,
            // top
            4,  5,  6,
            6,  7,  4,
            // back
            8,  9, 10,
            10, 11,  8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
        };
        
        // Buffers
        indices.Init(aIndices, 36, dry::DataTypeUShort, false);
        vertices.Init(aVertices, 24, dry::DataTypeVec3, false);
        texCoords.Init(aTexcoords, 24, dry::DataTypeVec2, false);
        
        // Texture
        dry::ImageUtils::Load(texture, dry::GetFilePath("grid.jpg"), dry::Texture::Params(true, true, false));
        
        // Shader
        shader.Init(dry::Shaders::Texture2D_VS, dry::Shaders::Texture2D_FS);
        shader.GetUniformByName("Texture")->Update(0);
        shader.GetAttribByName("Position")->SetVbo(&vertices);
        shader.GetAttribByName("TexCoord")->SetVbo(&texCoords);

        int w = GetParams().Width;
        int h = GetParams().Height;

        // Fbo
        fbo.Init(m_Renderer, dry::Fbo::Params(w,h));
        
        // Perspective
        cameraP.Init(45.f, (float)w / h, 0.1f, 10000.f);
        cameraP.LookAt(glm::vec3(0.0, 3.0, -8.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        // Orthogonal
        cameraO.Init(0,w, 0,h, 0.1f,10000.f);
        cameraO.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        
        // QuadBatch
        quadBatch.Init(m_Renderer);
        
        // Semi transparent background in FBO
        m_Renderer->SetClearColor(glm::vec4(0,0,0,0.75f), 1, 0);
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        int w = GetParams().Width;
        int h = GetParams().Height;
        
        // Bind Fbo
        fbo.Bind();
        
        m_Renderer->Clear(true, true, false);
        
        // Bind Shader
        shader.Bind();
        
        // Matrices
        float angle = GetTimer().GetTime() * 45;
        glm::mat4 anim = glm::rotate(angle, glm::vec3(0, 1, 0));
        glm::mat4 model = glm::translate(glm::vec3(0.0, 0.0, 0.0));
        shader.GetUniformByName("Model")->Update(model * anim);
        shader.GetUniformByName("View")->Update(cameraP.GetView());
        shader.GetUniformByName("Projection")->Update(cameraP.GetProjection());
        shader.GetUniformByName("Projection")->Update(0);

        // Buffers
        texture.Bind(0);
        indices.Bind();
        
        // Draw!
        m_Renderer->DrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT);
        
        // Unbind
        indices.Unbind();
        shader.Unbind();
        fbo.Unbind();

        // Draw background
        quadBatch.DrawTexture(&texture, &cameraO, glm::mat4(), 0,0, w,h);

        // Clear depth only
        m_Renderer->Clear(false, true, false);
    
        // Matrices
        shader.GetUniformByName("Model")->Update(model * anim);
        shader.GetUniformByName("View")->Update(cameraP.GetView());
        shader.GetUniformByName("Projection")->Update(cameraP.GetProjection());
        shader.GetUniformByName("Texture")->Update(0);
        fbo.GetTextureColor()->Bind(0);

        // Bind Shader
        shader.Bind();
        indices.Bind();
        
        m_Renderer->DrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT);
        
        indices.Unbind();
        shader.Unbind();
    }

private:
    
    dry::CameraPerspective  cameraP;
    dry::CameraOrthogonal   cameraO;
    dry::Shader             shader;
    dry::Texture            texture;
    dry::Fbo                fbo;
    dry::QuadBatch          quadBatch;
    dry::Vbo                vertices;
    dry::Vbo                texCoords;
    dry::Ibo                indices;
};

#endif