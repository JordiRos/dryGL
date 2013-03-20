//
//  Material.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Material.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Constructor
//
//------------------------------------------------------------------------------------------------
Material::Material()
{
    m_Shader = NULL;
}


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Material::Init(Shader *shader)
{
    m_Shader = shader;
    int uniforms = 0;
    glGetProgramiv(m_Shader->GetHandleProgram(), GL_ACTIVE_UNIFORMS, &uniforms);
    for (int i = 0; i < uniforms; ++i)
    {
        int len = 0;
        int num = 0;
        char name[100];
        GLenum type = GL_ZERO;
        glGetActiveUniform(m_Shader->GetHandleProgram(), (GLuint)i, sizeof(name)-1, &len, &num, &type, name);
        name[len] = 0;
        GLuint location = glGetUniformLocation(m_Shader->GetHandleProgram(), name);
    }
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Material::Free()
{
    m_Shader = NULL;
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void Material::Bind()
{
}
    