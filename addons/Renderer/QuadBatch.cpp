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
    glGenBuffers(1, (GLuint *)&m_Vertices);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // TexCoords
    GLfloat texcoords[2*4] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
    };
    glGenBuffers(1, (GLuint *)&m_TexCoords);
    glBindBuffer(GL_ARRAY_BUFFER, m_TexCoords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

    // Indices
    GLushort indices[] = {
        0,  1,  2,
        2,  3,  0,
    };
    glGenBuffers(1, (GLuint *)&m_Indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void QuadBatch::Free()
{
    if (m_Vertices > 0)
    {
        // Delete buffers
        glDeleteBuffers(1, (GLuint *)&m_Vertices);
        glDeleteBuffers(1, (GLuint *)&m_TexCoords);
        glDeleteBuffers(1, (GLuint *)&m_Indices);
        m_Vertices  = 0;
        m_TexCoords = 0;
        m_Indices   = 0;
    }
}


//------------------------------------------------------------------------------------------------
// Draw Texture
//
//------------------------------------------------------------------------------------------------
void QuadBatch::Draw(Texture const *texture, Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h)
{
    glActiveTexture(GL_TEXTURE0);
    texture->Bind();
    Draw(texture->GetHandle(), camera, shader, transform, x,y, w,h);
    texture->Unbind();
}


//------------------------------------------------------------------------------------------------
// Draw Fbo
//
//------------------------------------------------------------------------------------------------
void QuadBatch::Draw(Fbo const *fbo, Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h)
{
    glActiveTexture(GL_TEXTURE0);
    fbo->BindFboColor();
    Draw(fbo->GetFboColor(), camera, shader, transform, x,y, w,h);
    fbo->UnbindFboColor();
}


//------------------------------------------------------------------------------------------------
// Draw internal
//
//------------------------------------------------------------------------------------------------
void QuadBatch::Draw(int texture, Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h)
{
    shader->Bind();
    
    // Attributes/Uniforms
    int program = shader->GetHandleProgram();
    int aPosition = glGetAttribLocation (program, "Position");
    int aTexCoord = glGetAttribLocation (program, "TexCoord");
    int uMvp      = glGetUniformLocation(program, "ModelViewProjection");
    int uTexture  = glGetUniformLocation(program, "Texture");

    // Mvp
    float hw = w * 0.5f;
    float hh = h * 0.5f;
    glm::mat4 model = glm::translate(x + hw, y + hh, 0.f) * glm::scale(hw, hh, 1.f);
    glm::mat4 const &mvp = camera->GetMatProj() * camera->GetMatView() * model;
    glUniformMatrix4fv(uMvp, 1, GL_FALSE, glm::value_ptr(mvp));

    // Texture
    glUniform1i(uTexture, 0);

    // Vertices
    glEnableVertexAttribArray(aPosition);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vertices);
    glVertexAttribPointer(aPosition,        // attribute
                          3,                // number of elements per vertex, here (x,y,z)
                          GL_FLOAT,         // the type of each element
                          GL_FALSE,         // take our values as-is
                          0,                // no extra data between each position
                          0                 // offset of first element
                          );

    // TexCoords
    glEnableVertexAttribArray(aTexCoord);
    glBindBuffer(GL_ARRAY_BUFFER, m_TexCoords);
    glVertexAttribPointer(aTexCoord,        // attribute
                          2,                // number of elements per vertex, here (x,y)
                          GL_FLOAT,         // the type of each element
                          GL_FALSE,         // take our values as-is
                          0,                // no extra data between each position
                          0                 // offset of first element
                          );

    // Index
    int size;
    glBindBuffer          (GL_ELEMENT_ARRAY_BUFFER, m_Indices);
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements        (GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    
    // Unbind
    glDisableVertexAttribArray(aPosition);
    glDisableVertexAttribArray(aTexCoord);
    
    shader->Unbind();
}

