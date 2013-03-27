//
//  AppFbo.h
//
//  Example: How to render to texture using Fbo
//

#pragma once

#include "dry.h"
#include "QuadBatch.h"

class AppFbo : public dry::AppiOS
{
public:
    
dry::CameraPerspective  CameraP;
dry::CameraOrthogonal   CameraO;
dry::ShaderBasic        Shader;
dry::Texture            Texture;
dry::Fbo                Fbo;
dry::QuadBatch          QuadBatch;
dry::Vbo                Vertices;
dry::Vbo                TexCoords;
dry::Ibo                Indices;

AppFbo(dry::AppParams const &params) : dry::AppiOS(params) { }
    
//------------------------------------------------------------------------------------------------
// OnInit
//------------------------------------------------------------------------------------------------
void OnInit()
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
    dry::ImageLoader::LoadTexture(Texture, dry::GetFilePath("grid.jpg"), dry::Texture::Params(true, true));
    
    // Shader
    Shader.Init();

    int w = GetParams().Width;
    int h = GetParams().Height;

    // Fbo
    Fbo.Init(GetRenderer(), dry::Fbo::Params(w,h));
    
    // Perspective
    CameraP.Init(45.f, (float)w / h, 0.1f, 10000.f);
    CameraP.LookAt(glm::vec3(0.0, 2.0, -8.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    // Orthogonal
    CameraO.Init(0,w, 0,h, 0.1f,10000.f);
    CameraO.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    
    // QuadBatch
    QuadBatch.Init(GetRenderer());
}

//------------------------------------------------------------------------------------------------
// OnDraw
//------------------------------------------------------------------------------------------------
void OnDraw()
{
    int w = GetParams().Width;
    int h = GetParams().Height;
    
    // Bind Fbo
    Fbo.Bind();
    
    GetRenderer()->Clear(true, true, false);
    
    // Bind Shader
    Shader.Bind();
    
    // Matrices
    float angle = GetTimer().GetTime() * 45;
    glm::mat4 anim = glm::rotate(angle, glm::vec3(0, 1, 0));
    glm::mat4 model = glm::translate(glm::vec3(0.0, 0.0, 0.0));
    glm::mat4 mvp = CameraP.GetMatProj() * CameraP.GetMatView() * model * anim;
    glUniformMatrix4fv(Shader.GetUniformLocation("ModelViewProjection"), 1, GL_FALSE, glm::value_ptr(mvp));

    // Buffers
    Texture.Bind(0);
    glUniform1i(Shader.GetUniformLocation("Texture"), 0);
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
    
    Fbo.Unbind();
    
    // Draw background + Fbo to screen using quadbatch
    glDisable(GL_DEPTH_TEST);
    QuadBatch.DrawTexture(&Texture, &CameraO, glm::mat4(), 0.f,0.f, w,h);
    QuadBatch.DrawTexture(Fbo.GetTextureColor(), &CameraO, anim, w/4.f,h/4.f, w/2.f, h/2.f);
    glEnable(GL_DEPTH_TEST);
}

};
