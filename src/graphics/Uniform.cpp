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
// Create
//
//------------------------------------------------------------------------------------------------
Uniform *Uniform::Create(int location, int gltype)
{
    switch (gltype)
    {
        case GL_INT:
        case GL_SAMPLER_2D:
        case GL_SAMPLER_CUBE: return NEW UniformT<int>      (location);
        case GL_FLOAT:        return NEW UniformT<float>    (location);
        case GL_FLOAT_VEC2:   return NEW UniformT<glm::vec2>(location);
        case GL_FLOAT_VEC3:   return NEW UniformT<glm::vec3>(location);
        case GL_FLOAT_VEC4:   return NEW UniformT<glm::vec4>(location);
        case GL_FLOAT_MAT3:   return NEW UniformT<glm::mat3>(location);
        case GL_FLOAT_MAT4:   return NEW UniformT<glm::mat4>(location);
        default:              assert(false);
    }
    return NULL;
}
    

//------------------------------------------------------------------------------------------------
// Submit template specializations
//
//------------------------------------------------------------------------------------------------
template<>
void UniformT<int>::Bind()
{
    if (m_Submit)
    {
        glUniform1i(m_Location, m_Value);
        m_Submit = false;
    }
}

template<>
void UniformT<float>::Bind()
{
    if (m_Submit)
    {
        glUniform1f(m_Location, m_Value);
        m_Submit = false;
    }
}

template<>
void UniformT<glm::vec2>::Bind()
{
    if (m_Submit)
    {
        glUniform2fv(m_Location, 1, glm::value_ptr(m_Value));
        m_Submit = false;
    }
}

template<>
void UniformT<glm::vec3>::Bind()
{
    if (m_Submit)
    {
        glUniform3fv(m_Location, 1, glm::value_ptr(m_Value));
        m_Submit = false;
    }
}

template<>
void UniformT<glm::vec4>::Bind()
{
    if (m_Submit)
    {
        glUniform4fv(m_Location, 1, glm::value_ptr(m_Value));
        m_Submit = false;
    }
}

template<>
void UniformT<glm::mat3>::Bind()
{
    if (m_Submit)
    {
        glUniformMatrix3fv(m_Location, 1, false, glm::value_ptr(m_Value));
        m_Submit = false;
    }
}

template<>
void UniformT<glm::mat4>::Bind()
{
    if (m_Submit)
    {
        glUniformMatrix4fv(m_Location, 1, false, glm::value_ptr(m_Value));
        m_Submit = false;
    }
}
