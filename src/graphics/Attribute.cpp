//
//  Attribute.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Attribute.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Attribute
//
//------------------------------------------------------------------------------------------------
bool Attribute::Init(Shader *shader, string const &name, int size, DataType type, bool dynamic)
{
    bool res = false;
    if (GetDataTypeAttribute(type))
    {
        m_Attribute = shader->GetAttribLocation(name.c_str());
        m_Type      = type;
        m_Size      = size;
        m_Name      = name;
        m_Update    = false;
        m_Vbo.Init(NULL, m_Size, m_Type, dynamic);
        m_Data = NEW_ARRAY(uchar, m_Size * GetDataTypeSize(type));
        res = true;
    }
    else
        dry::Log(LogWarning, "[Attribute] Error creating Attribute with type: %d and size: %d", type, size);
    return res;
}


//------------------------------------------------------------------------------------------------
// Attribute
//
//------------------------------------------------------------------------------------------------
bool Attribute::Init(Shader *shader, int idx, int size, bool dynamic)
{
    bool res = false;
    // Load info from shader
    char name[128];
    int len  = 0;
    int num  = 0;
    int type = 0;
    glGetActiveAttrib(shader->GetHandleProgram(), (GLuint)idx, sizeof(name)-1, &len, &num, (GLenum *)&type, name);
    if (len > 0)
    {
        name[len] = 0;
        DataType dataType = GetDataTypeWithGLType(type);
        if (GetDataTypeAttribute(dataType))
        {
            m_Attribute = glGetAttribLocation(shader->GetHandleProgram(), name);
            m_Type      = dataType;
            m_Size      = size;
            m_Name      = name;
            m_Update    = false;
            m_Vbo.Init(NULL, m_Size, m_Type, dynamic);
            m_Data = NEW_ARRAY(uchar, m_Size * GetDataTypeSize(dataType));
            res = true;
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
void Attribute::Free()
{
    m_Vbo.Free();
    DISPOSE_ARRAY(m_Data);
}


//------------------------------------------------------------------------------------------------
// Update
//
//------------------------------------------------------------------------------------------------
void Attribute::Update(bool now)
{
    m_Update = true;
    if (now && m_Data)
    {
        m_Vbo.Update(m_Data, m_Size, 0);
        m_Update = false;
    }
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void Attribute::Bind()
{
    if (m_Update)
        Update(true);
    m_Vbo.Bind(m_Attribute);
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void Attribute::Unbind()
{
    m_Vbo.Unbind();
}
