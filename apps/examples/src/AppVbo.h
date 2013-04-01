//
//  AppVbo.h
//
//  Example: How to setup VertexBufferObjects and use them for custom rendering
//

#pragma once

#include "dry.h"
#include "Shaders.h"

class AppVbo : public dry::AppiOS
{
public:
    
    AppVbo(dry::AppParams const &params) : dry::AppiOS(params) { }

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
        dry::ImageUtils::Load(texture, dry::GetFilePath("grid.jpg"), dry::Texture::Params(false, false, false));
        
        // Shader
        shader.Load(dry::Shaders::Texture2D_VS, dry::Shaders::Texture2D_FS);
        
        // Camera
        int w = GetParams().Width;
        int h = GetParams().Height;
        camera.Init(45.f, (float)w / h, 0.1f, 10000.f);
        camera.LookAt(glm::vec3(0.0, 2.0, -8.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        
        // Uniforms
        uTexture = shader.GetUniformByName("Texture");
        uTexture->Update(0);
        uModel = shader.GetUniformByName("Model");
        uView = shader.GetUniformByName("View");
        uProjection = shader.GetUniformByName("Projection");
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        m_Renderer->Clear(true, true, false);
        
        // Update uniform values
        float angle = GetTimer().GetTime() * 45;
        glm::mat4 rotation = glm::rotate(angle, glm::vec3(0, 1, 0));
        glm::mat4 position = glm::translate(glm::vec3(0.0, 0.0, 0.0));
        uModel->Update(position * rotation);
        uView->Update(camera.GetMatView());
        uProjection->Update(camera.GetMatProjection());

        // Bind
        texture.Bind(0);
        shader.Bind();

        // Buffers
        vertices.Bind(shader.GetAttribByName("Position"));
        texCoords.Bind(shader.GetAttribByName("TexCoord"));
        indices.Bind();
        
        // Draw!
        m_Renderer->DrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT);
        
        // Unbind
        vertices.Unbind();
        texCoords.Unbind();
        indices.Unbind();
    }

private:

    dry::CameraPerspective  camera;
    dry::Shader             shader;
    dry::Texture            texture;
    dry::Vbo                vertices;
    dry::Vbo                texCoords;
    dry::Ibo                indices;
    dry::UniformInterface  *uTexture;
    dry::UniformInterface  *uModel;
    dry::UniformInterface  *uView;
    dry::UniformInterface  *uProjection;
};
