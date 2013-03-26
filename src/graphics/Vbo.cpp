//
//  Vbo.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Vbo.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Vbo::Init(void const *data, int size, DataType type, bool dynamic)
{
    bool res = false;
    if (GetDataTypeVbo(type))
    {
        m_Size      = size;
        m_Type      = type;
        m_TypeSize  = GetDataTypeSize    (type);
        m_Elements  = GetDataTypeElements(type);
        m_GLType    = GetDataTypeGLType  (type);
        m_Dynamic   = dynamic;
        m_Attribute = 0;
        // Create GL buffers
        glGenBuffers(1, (GLuint *)&m_Vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
        glBufferData(GL_ARRAY_BUFFER, m_Size * m_TypeSize, data, m_Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        res = true;
    }
    else
        dry::Log(LogWarning, "[Vbo] Error creating VertexBufferObject with type: %d and size: %d", type, size);

    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Vbo::Free()
{
    if (m_Vbo > 0)
    {
        glDeleteBuffers(1, (GLuint *)&m_Vbo);
        m_Vbo = 0;
    }
}


//------------------------------------------------------------------------------------------------
// Update
//
//------------------------------------------------------------------------------------------------
void Vbo::Update(void const *data, int size, int offset)
{
    glBindBuffer   (GL_ARRAY_BUFFER, m_Vbo);
    glBufferSubData(GL_ARRAY_BUFFER, offset, m_Size * m_TypeSize, data);
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void Vbo::Bind(int attribute)
{
    m_Attribute = attribute;
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glEnableVertexAttribArray(m_Attribute);
    glVertexAttribPointer    (m_Attribute, m_Elements, m_GLType, GL_FALSE, 0, 0);
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void Vbo::Unbind()
{
    if (m_Attribute > 0)
    {
        glDisableVertexAttribArray(m_Attribute);
        m_Attribute = 0;
    }
}
