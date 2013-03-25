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
bool Uniform::Init(int uniform, UniformType type)
{
    bool res = false;
    if (type != UniformTypeUnknown)
    {
        m_Uniform = uniform;
        m_Type = type;
        res = true;
    }
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
        case UniformTypeInt:     glUniform1i        (m_Uniform, Value.i); break;
        case UniformTypeFloat:   glUniform1f        (m_Uniform, Value.f); break;
        case UniformTypeVec2:    glUniform2fv       (m_Uniform, 1, glm::value_ptr(Value.v2)); break;
        case UniformTypeVec3:    glUniform3fv       (m_Uniform, 1, glm::value_ptr(Value.v3)); break;
        case UniformTypeVec4:    glUniform4fv       (m_Uniform, 1, glm::value_ptr(Value.v4)); break;
        case UniformTypeMat2:    glUniformMatrix2fv (m_Uniform, 1, false, glm::value_ptr(Value.m2)); break;
        case UniformTypeMat3:    glUniformMatrix3fv (m_Uniform, 1, false, glm::value_ptr(Value.m3)); break;
        case UniformTypeMat4:    glUniformMatrix4fv (m_Uniform, 1, false, glm::value_ptr(Value.m4)); break;
        case UniformTypeTex2D:   glUniform1i        (m_Uniform, Value.i); break;
        case UniformTypeTexCube: glUniform1i        (m_Uniform, Value.i); break;
        case UniformTypeUnknown:
            dry::Log(LogWarning, "[MaterialUniform] Unknown UniformType specified");
            break;
    }
}
