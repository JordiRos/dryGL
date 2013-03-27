//
//  Ibo.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Ibo.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Ibo::Init(void const *data, int size, DataType type, bool dynamic)
{
    bool res = false;
    if (GetDataTypeIbo(type))
    {
        m_Size     = size;
        m_Type     = type;
        m_TypeSize = GetDataTypeSize (m_Type);
        m_GLVar    = GetDataTypeGLVar(m_Type);
        m_Dynamic  = dynamic;
        // Create GL buffers
        glGenBuffers(1, (GLuint *)&m_Ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Size * m_TypeSize, data, m_Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        res = true;
    }
    else
        dry::Log(LogWarning, "[Ibo] Error creating IndexBufferObject with type: %d and size: %d", type, size);
    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Ibo::Free()
{
    if (m_Ibo > 0)
    {
        glDeleteBuffers(1, (GLuint *)&m_Ibo);
        m_Ibo = 0;
    }
}


//------------------------------------------------------------------------------------------------
// Update
//
//------------------------------------------------------------------------------------------------
void Ibo::Update(void const *data, int size, int offset)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, m_Size * m_TypeSize, data);
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void Ibo::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void Ibo::Unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
