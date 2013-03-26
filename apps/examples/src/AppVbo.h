//
//  AppVbo.h
//
//  Example: How to setup VertexBufferObjects and use them for custom rendering
//

#pragma once

#include "dry.h"

class AppVbo : public dry::AppiOS
{
public:

dry::CameraPerspective  Camera;
dry::ShaderBasic        Shader;
dry::Texture            Texture;
dry::Vbo                Vertices;
dry::Vbo                TexCoords;
dry::Ibo                Indices;
dry::Uniform            UTexture;
dry::Uniform            UModelViewProjection;

AppVbo(dry::AppParams const &params) : dry::AppiOS(params) { }
    
void Init()
{
    // Vertices
    GLfloat vertices[] = {
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
    GLfloat texcoords[2*4*6] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
    };
    for (int i = 1; i < 6; i++)
        memcpy(&texcoords[i*4*2], &texcoords[0], 2*4*sizeof(GLfloat));
    // Indices
    GLushort indices[] = {
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
    Indices.Init(indices, 36, dry::DataTypeUShort, false);
    Vertices.Init(vertices, 24, dry::DataTypeVec3, false);
    TexCoords.Init(texcoords, 24, dry::DataTypeVec2, false);

    // Texture
    dry::ImageLoader::LoadTexture(Texture, dry::GetFilePath("metal.png"), dry::Texture::Params(true, false));
    
    // Shader
    Shader.Init();
    
    // Camera
    int w = GetParams().Width;
    int h = GetParams().Height;
    Camera.Init(45.f, (float)w / h, 0.1f, 10000.f);
    Camera.LookAt(glm::vec3(0.0, 2.0, -8.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    
    // Uniforms
    UTexture.Init(Shader.GetUniformLocation("Texture"), dry::DataTypeTex2D);
    UModelViewProjection.Init(Shader.GetUniformLocation("ModelViewProjection"), dry::DataTypeMat4);
}

void Draw()
{
    GetRenderer()->Clear(true, true, false);
    
    // Bind
    Shader.Bind();

    // Matrices
    float angle = GetTimer().GetTime() * 45;
    glm::mat4 anim = glm::rotate(angle, glm::vec3(0, 1, 0));
    glm::mat4 model = glm::translate(glm::vec3(0.0, 0.0, 0.0));
    UModelViewProjection.Value = Camera.GetMatProj() * Camera.GetMatView() * model * anim;
    UModelViewProjection.Bind();

    // Buffers
    int stage = 1; // Bind texture to stage, set uniform to stage
    Texture.Bind(stage);
    UTexture.Value = stage;
    UTexture.Bind();
    Vertices.Bind(Shader.GetAttribLocation("Position"));
    TexCoords.Bind(Shader.GetAttribLocation("TexCoord"));
    Indices.Bind();
    
    // Draw!
    GetRenderer()->DrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT);
    
    // Unbind
    Texture.Unbind();
    Vertices.Unbind();
    TexCoords.Unbind();
    Indices.Unbind();
    Shader.Unbind();
}

};
