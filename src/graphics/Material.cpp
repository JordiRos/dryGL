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
// Init
//
//------------------------------------------------------------------------------------------------
bool Material::Init(Shader *shader)
{
    bool res = false;
    m_Shader = shader;
    
    if (m_Shader)
    {
        // Load uniforms
        int uniforms = 0;
        glGetProgramiv(m_Shader->GetHandleProgram(), GL_ACTIVE_UNIFORMS, &uniforms);
        for (int i = 0; i < uniforms; ++i)
        {
            Uniform *uniform = NEW Uniform();
            if (uniform->Init(m_Shader, i))
                m_Uniforms[uniform->GetName()] = uniform;
            else
                DISPOSE(uniform);
        }
        // Load attributes
        int attributes = 0;
        glGetProgramiv(m_Shader->GetHandleProgram(), GL_ACTIVE_ATTRIBUTES, &attributes);
        for (int i = 0; i < attributes; ++i)
        {
            Attribute *attribute = NEW Attribute();
            if (attribute->Init(m_Shader, i, 0, false))
                m_Attributes[attribute->GetName()] = attribute;
            else
                DISPOSE(attribute);
        }
    }
    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Material::Free()
{
    m_Shader = NULL;
    // Free uniforms
    for (map<string,Uniform *>::iterator iter = m_Uniforms.begin(); iter != m_Uniforms.end(); ++iter)
    {
        Uniform *uniform = iter->second;
        DISPOSE(uniform);
        iter->second = NULL;
    }
    m_Uniforms.clear();
    // Free attributes
    for (map<string,Attribute *>::iterator iter = m_Attributes.begin(); iter != m_Attributes.end(); ++iter)
    {
        Attribute *attribute = iter->second;
        DISPOSE(attribute);
        iter->second = NULL;
    }
    m_Attributes.clear();    
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void Material::Bind()
{
    // Uniforms
    for (map<string,Uniform *>::iterator iter = m_Uniforms.begin(); iter != m_Uniforms.end(); ++iter)
    {
        Uniform *uniform = iter->second;
        uniform->Bind();
    }
    // Attributes
    for (map<string,Attribute *>::iterator iter = m_Attributes.begin(); iter != m_Attributes.end(); ++iter)
    {
        Attribute *attribute = iter->second;
        attribute->Bind();
    }
}
