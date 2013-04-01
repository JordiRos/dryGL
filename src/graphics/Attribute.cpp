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
    Free();
    if (GetDataTypeAttribute(type))
    {
        m_Attribute = shader->GetAttribByName(name);
        m_Name      = name;
        m_Update    = false;
        m_Vbo.Init(NULL, size, type, dynamic);
        if (m_Vbo.GetSize())
            m_Data = NEW_ARRAY(uchar, m_Vbo.GetSize() * m_Vbo.GetTypeSize());
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
//    Free();
//    // Load info from shader
//    char name[128];
//    int len = 0;
//    int num = 0;
//    int gltype = 0;
//    glGetActiveAttrib(shader->GetHandleProgram(), (GLuint)idx, sizeof(name)-1, &len, &num, (GLenum *)&gltype, name);
//    if (len > 0)
//    {
//        name[len] = 0;
//        DataType type = GetDataTypeWithGLType(gltype);
//        if (GetDataTypeAttribute(type))
//        {
//            m_Attribute = glGetAttribLocation(shader->GetHandleProgram(), name);
//            m_Name      = name;
//            m_Update    = false;
//            m_Vbo.Init(NULL, size, type, dynamic);
//            if (m_Vbo.GetSize())
//                m_Data = NEW_ARRAY(uchar, m_Vbo.GetSize() * m_Vbo.GetTypeSize());
//            res = true;
//        }
//        else
//            dry::Log(LogWarning, "[Uniform] Unsupported data type in uniform: %d", type);
//    }
//    else
//        dry::Log(LogWarning, "[Uniform] Can't find Uniform with index %d", idx);
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
// Resize
//
//------------------------------------------------------------------------------------------------
void Attribute::Resize(int size)
{
    DISPOSE_ARRAY(m_Data);
    m_Data = NEW_ARRAY(uchar, size * m_Vbo.GetTypeSize());
    m_Vbo.Resize(m_Data, size);
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
        m_Vbo.Update(m_Data, m_Vbo.GetSize(), 0);
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
