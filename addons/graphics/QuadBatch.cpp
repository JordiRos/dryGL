//
//  QuadBatch.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "QuadBatch.h"
#include "Shaders.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
void QuadBatch::Init(Renderer *renderer)
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
    
    m_Renderer = renderer;
    
    // Buffers
    m_Vertices.Init(vertices, 4, DataTypeVec3, false);
    m_TexCoords.Init(texcoords, 4, DataTypeVec2, false);
    m_Indices.Init(indices, 6, DataTypeUShort, false);
    // Shader
    m_Shader.Init(Shaders::Texture2D_VS, Shaders::Texture2D_FS);
    m_Shader.GetUniformByName("Texture")->Update(0);
    m_Shader.GetAttribByName("Position")->SetVbo(&m_Vertices);
    m_Shader.GetAttribByName("TexCoord")->SetVbo(&m_TexCoords);
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void QuadBatch::Free()
{
}


//------------------------------------------------------------------------------------------------
// DrawTexture
//
//------------------------------------------------------------------------------------------------
void QuadBatch::DrawTexture(Texture *texture, Camera const *camera, glm::mat4 const &transform, float x, float y, float w, float h)
{
    texture->Bind(0);
    DrawShader(&m_Shader, camera, transform, x,y, w,h);
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
    
    // TODO: Not to be queried every time
    shader->GetUniformByName("Model")->Update(model * transform);
    shader->GetUniformByName("View")->Update(camera->GetView());
    shader->GetUniformByName("Projection")->Update(camera->GetProjection());

    m_Shader.Bind();
    m_Indices.Bind();

    // Draw!
    m_Renderer->DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT);

    m_Indices.Unbind();    
    m_Shader.Unbind();
}
