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
bool Ibo::Init(void const *data, int size, int type, bool dynamic)
{
    bool res = false;
    int typeSize = 0;
    int dataType = 0;
    switch (type)
    {
        case GL_UNSIGNED_BYTE:  typeSize = sizeof(GLubyte);  dataType = GL_UNSIGNED_BYTE;  break;
        case GL_UNSIGNED_SHORT: typeSize = sizeof(GLushort); dataType = GL_UNSIGNED_SHORT; break;
        case GL_UNSIGNED_INT:   typeSize = sizeof(GLuint);   dataType = GL_UNSIGNED_INT;   break;
    }
    if (typeSize > 0)
    {
        m_Size     = size;
        m_Type     = type;
        m_TypeSize = typeSize;
        m_DataType = dataType;
        m_Dynamic  = dynamic;
        // Create GL buffers
        glGenBuffers(1, (GLuint *)&m_Ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Size * m_TypeSize, data, m_Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        res = true;
    }
    else
        dry::Log(LogWarning, "[Ibo] Error creating IndexBufferObject with size %d", size);
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


//------------------------------------------------------------------------------------------------
// Draw
//
//------------------------------------------------------------------------------------------------
void Ibo::Draw(int primitive)
{
    glDrawElements(primitive, m_Size, m_DataType, 0);
}
