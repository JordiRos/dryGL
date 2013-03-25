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
    
    // Buffers
    m_Vertices.Init(vertices, 4, GL_FLOAT_VEC3, false);
    m_TexCoords.Init(texcoords, 4, GL_FLOAT_VEC2, false);
    m_Indices.Init(indices, 6, GL_UNSIGNED_SHORT, false);
    // Shader
    m_Shader.Init();
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
void QuadBatch::DrawTexture(Texture *texture, Camera const *camera, glm::mat4 const &transform, float x, float y, float w, float h)
{
    m_Shader.Bind();
    texture->Bind(0);

    DrawShader(&m_Shader, camera, transform, x,y, w,h);

    texture->Unbind();
    m_Shader.Unbind();
}


//------------------------------------------------------------------------------------------------
// Draw Fbo
//
//------------------------------------------------------------------------------------------------
void QuadBatch::DrawFbo(Fbo *fbo, Camera const *camera, glm::mat4 const &transform, float x, float y, float w, float h)
{
    m_Shader.Bind();
    fbo->BindFboColor(0);
    glUniform1i(m_Shader.GetUniformLocation("Texture"), 0);
    
    DrawShader(&m_Shader, camera, transform, x,y, w,h);

    fbo->UnbindFboColor();
    m_Shader.Unbind();
}


//------------------------------------------------------------------------------------------------
// Draw a shader
//
//------------------------------------------------------------------------------------------------
void QuadBatch::DrawShader(Shader *shader, Camera const *camera, glm::mat4 const &transform, float x, float y, float w, float h)
{
    // Mvp
    float hw = w * 0.5f;
    float hh = h * 0.5f;
    glm::mat4 model = glm::translate(x + hw, y + hh, 0.f) * glm::scale(hw, hh, 1.f);
    glm::mat4 const &mvp = camera->GetMatProj() * camera->GetMatView() * model * transform;
    glUniformMatrix4fv(shader->GetUniformLocation("ModelViewProjection"), 1, GL_FALSE, glm::value_ptr(mvp));

    // Bind
    m_Vertices.Bind(shader->GetAttribLocation("Position"));
    m_TexCoords.Bind(shader->GetAttribLocation("TexCoord"));
    m_Indices.Bind();

    // Draw!
    m_Indices.Draw(GL_TRIANGLES);

    // Unbind
    m_Vertices.Unbind();
    m_TexCoords.Unbind();
    m_Indices.Unbind();
}
