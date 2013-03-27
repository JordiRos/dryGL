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
bool Uniform::Init(int uniform, DataType type)
{
    bool res = false;
    if (GetDataTypeUniform(type))
    {
        m_Uniform = uniform;
        m_Type = type;
        res = true;
    }
    else
        dry::Log(LogWarning, "[Uniform] Error creating Attribute with type: %d", type);

    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Uniform::Free()
{
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void Uniform::Bind()
{
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
        case DataTypeTex2D:    if (m_Value.tex.tex)  { m_Value.tex.tex ->Bind     (m_Value.tex.stage);  glUniform1i(m_Uniform, m_Value.tex.stage ); } break;
        case DataTypeTexCube:  if (m_Value.cube.tex) { m_Value.cube.tex->Bind     (m_Value.cube.stage); glUniform1i(m_Uniform, m_Value.cube.stage); } break;
        case DataTypeFboColor: if (m_Value.fbo.fbo)  { m_Value.fbo.fbo ->BindColor(m_Value.fbo.stage);  glUniform1i(m_Uniform, m_Value.fbo.stage ); } break;
        case DataTypeFboDepth: if (m_Value.fbo.fbo)  { m_Value.fbo.fbo ->BindDepth(m_Value.fbo.stage);  glUniform1i(m_Uniform, m_Value.fbo.stage ); } break;
        default: dry::Log(LogWarning, "[Uniform] Unsupported DataType specified"); break;
    }
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void Uniform::Unbind()
{
    switch (m_Type)
    {
        case DataTypeTex2D:    if (m_Value.tex.tex)  { m_Value.tex.tex ->Unbind     (); } break;
        case DataTypeTexCube:  if (m_Value.cube.tex) { m_Value.cube.tex->Unbind     (); } break;
        case DataTypeFboColor: if (m_Value.fbo.fbo)  { m_Value.fbo.fbo ->UnbindColor(); } break;
        case DataTypeFboDepth: if (m_Value.fbo.fbo)  { m_Value.fbo.fbo ->UnbindDepth(); } break;
        default: break;
    }
}
