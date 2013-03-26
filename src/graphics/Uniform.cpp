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
        case DataTypeInt:     glUniform1i        (m_Uniform, Value.i); break;
        case DataTypeFloat:   glUniform1f        (m_Uniform, Value.f); break;
        case DataTypeVec2:    glUniform2fv       (m_Uniform, 1, glm::value_ptr(Value.v2)); break;
        case DataTypeVec3:    glUniform3fv       (m_Uniform, 1, glm::value_ptr(Value.v3)); break;
        case DataTypeVec4:    glUniform4fv       (m_Uniform, 1, glm::value_ptr(Value.v4)); break;
        case DataTypeMat2:    glUniformMatrix2fv (m_Uniform, 1, false, glm::value_ptr(Value.m2)); break;
        case DataTypeMat3:    glUniformMatrix3fv (m_Uniform, 1, false, glm::value_ptr(Value.m3)); break;
        case DataTypeMat4:    glUniformMatrix4fv (m_Uniform, 1, false, glm::value_ptr(Value.m4)); break;
        case DataTypeTex2D:   glUniform1i        (m_Uniform, Value.i); break;
        case DataTypeTexCube: glUniform1i        (m_Uniform, Value.i); break;
        default: dry::Log(LogWarning, "[MaterialUniform] Unsupported DataType specified"); break;
    }
}
