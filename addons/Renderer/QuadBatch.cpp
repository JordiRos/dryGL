//
//  QuadBatch.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "QuadBatch.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
void QuadBatch::Init()
{
    // Vertices
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
    };
    // TexCoords
    GLfloat texcoords[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
    };
    // Indices
    GLushort indices[] = {
        0,  1,  2,
        2,  3,  0,
    };
    
    // Vbo
    m_Vertices.Init(12, false, 3, vertices);
    m_TexCoords.Init(8, false, 2, texcoords);
    // Ibo
    m_Indices.Init(6, false, indices);
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void QuadBatch::Free()
{
}


//------------------------------------------------------------------------------------------------
// Draw Texture
//
//------------------------------------------------------------------------------------------------
void QuadBatch::Draw(Texture const *texture, Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h)
{
    shader->Bind();
    texture->Bind(shader->GetUniformLocation("Texture"), 0);

    Draw(camera, shader, transform, x,y, w,h);

    texture->Unbind();
    shader->Unbind();
}


//------------------------------------------------------------------------------------------------
// Draw Fbo
//
//------------------------------------------------------------------------------------------------
void QuadBatch::Draw(Fbo const *fbo, Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h)
{
    shader->Bind();
    fbo->BindFboColor(shader->GetUniformLocation("Texture"), 0);

    Draw(camera, shader, transform, x,y, w,h);

    fbo->UnbindFboColor();
    shader->Unbind();
}


//------------------------------------------------------------------------------------------------
// Draw internal
//
//------------------------------------------------------------------------------------------------
void QuadBatch::Draw(Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h)
{
    // Attributes/Uniforms
    int aPosition = shader->GetAttribLocation ("Position");
    int aTexCoord = shader->GetAttribLocation ("TexCoord");
    int uMvp      = shader->GetUniformLocation("ModelViewProjection");

    // Mvp
    float hw = w * 0.5f;
    float hh = h * 0.5f;
    glm::mat4 model = glm::translate(x + hw, y + hh, 0.f) * glm::scale(hw, hh, 1.f);
    glm::mat4 const &mvp = camera->GetMatProj() * camera->GetMatView() * model;
    glUniformMatrix4fv(uMvp, 1, GL_FALSE, glm::value_ptr(mvp));

    // Bind
    m_Vertices.Bind(aPosition);
    m_TexCoords.Bind(aTexCoord);
    m_Indices.Bind();

    // Draw!
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
    
    // Unbind
    m_Vertices.Unbind(aPosition);
    m_TexCoords.Unbind(aTexCoord);
    m_Indices.Unbind();
}

