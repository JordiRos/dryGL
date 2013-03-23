//
//  AppVbo.h
//  dryExamples
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "ImageLoader.h"


class AppVbo : public dry::AppiOS
{
public:

dry::CameraPerspective  Camera;
dry::ShaderBasic        Shader;
dry::Texture            Texture;
dry::Vbo<glm::vec3>     Vertices;
dry::Vbo<glm::vec2>     Texcoords;
dry::Ibo<ushort>        Indices;


AppVbo(dry::AppParams const &params) : dry::AppiOS(params)
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
    Indices.Init(36, false, indices);
    Vertices.Init(24, false, 3, (glm::vec3 *)vertices);
    Texcoords.Init(24, false, 2, (glm::vec2 *)texcoords);
    
    // Texture
    dry::ImageLoader::LoadTexture(dry::GetFilePath("metal.png"), Texture);
    
    // Shader
    Shader.Init();
    
    // Camera
    int w = GetParams().Width;
    int h = GetParams().Height;
    Camera.Init(45.f, (float)w / h, 0.1f, 100.f);
    Camera.LookAt(glm::vec3(0.0, 2.0, -8.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    
    // Viewport
    GetRenderer()->SetViewport(0,0, w,h);
}
    

void Draw()
{
    GetRenderer()->Clear(true, true, false);
    GetRenderer()->SetBlendMode(dry::BLEND_ALPHA);
    
    // Bind
    Shader.Bind();

    // Matrices
    float angle = GetTimer().GetTime() * 45;
    glm::mat4 anim = glm::rotate(angle, glm::vec3(0, 1, 0));
    glm::mat4 model = glm::translate(glm::vec3(0.0, 0.0, 0.0));
    glm::mat4 mvp = Camera.GetMatProj() * Camera.GetMatView() * model * anim;
    glUniformMatrix4fv(Shader.GetUniformLocation("ModelViewProjection"), 1, GL_FALSE, glm::value_ptr(mvp));

    // Buffers
    Texture.Bind(Shader.GetUniformLocation("Texture"), 0);
    Vertices.Bind(Shader.GetAttribLocation("Position"), false);
    Texcoords.Bind(Shader.GetAttribLocation("TexCoord"), false);
    Indices.Bind();
    
    // Draw!
    Indices.Draw(GL_TRIANGLES);
    
    // Unbind
    Vertices.Unbind();
    Texcoords.Unbind();
    Indices.Unbind();
    Texture.Unbind();
    Shader.Unbind();
}


};
