//
//  Uniform.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Uniform.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Uniform::Init(Shader *shader, string const &name, DataType type)
{
    bool res = false;
    Free();
    if (GetDataTypeUniform(type))
    {
        int uniform = shader->GetUniformLocation(name.c_str());
        if (uniform >= 0)
        {
            m_Uniform = uniform;
            m_Type    = type;
            m_Name    = name;
            res       = true;
        }
        else
            dry::Log(LogWarning, "[Uniform] Uniform %s not found", name.c_str());
    }
    else
        dry::Log(LogWarning, "[Uniform] Error creating Uniform with type: %d", type);
    
    return res;
}


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Uniform::Init(Shader *shader, int idx)
{
    bool res = false;
    Free();
    // Load info from shader
    char name[128];
    int len  = 0;
    int num  = 0;
    int type = 0;
    glGetActiveUniform(shader->GetHandleProgram(), (GLuint)idx, sizeof(name)-1, &len, &num, (GLenum *)&type, name);
    if (len > 0)
    {
        name[len] = 0;
        DataType dataType = GetDataTypeWithGLType(type);
        if (GetDataTypeUniform(dataType))
        {
            m_Uniform = glGetUniformLocation(shader->GetHandleProgram(), name);
            m_Type    = dataType;
            m_Name    = name;
            res       = true;
        }
        else
            dry::Log(LogWarning, "[Uniform] Unsupported data type in uniform: %d", dataType);
    }
    else
        dry::Log(LogWarning, "[Uniform] Can't find Uniform with index %d", idx);
    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Uniform::Free()
{
    m_Uniform = -1;
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void Uniform::Bind()
{
    if (!IsOk()) return;
    switch (m_Type)
    {
        case DataTypeInt:      glUniform1i           (m_Uniform, m_Value.i); break;
        case DataTypeFloat:    glUniform1f           (m_Uniform, m_Value.f); break;
        case DataTypeVec2:     glUniform2fv          (m_Uniform, 1, glm::value_ptr(m_Value.v2)); break;
        case DataTypeVec3:     glUniform3fv          (m_Uniform, 1, glm::value_ptr(m_Value.v3)); break;
        case DataTypeVec4:     glUniform4fv          (m_Uniform, 1, glm::value_ptr(m_Value.v4)); break;
        case DataTypeMat2:     glUniformMatrix2fv    (m_Uniform, 1, false, glm::value_ptr(m_Value.m2)); break;
        case DataTypeMat3:     glUniformMatrix3fv    (m_Uniform, 1, false, glm::value_ptr(m_Value.m3)); break;
        case DataTypeMat4:     glUniformMatrix4fv    (m_Uniform, 1, false, glm::value_ptr(m_Value.m4)); break;
        case DataTypeTex2D:    if (m_Value.tex.tex)  { m_Value.tex.tex ->Bind(m_Value.tex.stage);  glUniform1i(m_Uniform, m_Value.tex.stage ); } break;
        case DataTypeTexCube:  if (m_Value.cube.tex) { m_Value.cube.tex->Bind(m_Value.cube.stage); glUniform1i(m_Uniform, m_Value.cube.stage); } break;
        default: dry::Log(LogWarning, "[Uniform] Unsupported DataType specified"); break;
    }
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void Uniform::Unbind()
{
    if (!IsOk()) return;
    switch (m_Type)
    {
        case DataTypeTex2D:    if (m_Value.tex.tex)  { m_Value.tex.tex ->Unbind(); } break;
        case DataTypeTexCube:  if (m_Value.cube.tex) { m_Value.cube.tex->Unbind(); } break;
        default: break;
    }
}
