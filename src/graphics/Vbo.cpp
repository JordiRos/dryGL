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
bool Vbo::Init(void const *data, int size, int type, bool dynamic)
{
    bool res = false;
    int elements = 0;
    int typeSize = 0;
    int dataType = 0;
    switch (type)
    {
        case GL_INT:        elements = 1;  typeSize = sizeof(GLint);          dataType = GL_INT;   break;
        case GL_FLOAT:      elements = 1;  typeSize = sizeof(GLfloat);        dataType = GL_FLOAT; break;
        case GL_FLOAT_VEC2: elements = 2;  typeSize = sizeof(GLfloat) * 2.f;  dataType = GL_FLOAT; break;
        case GL_FLOAT_VEC3: elements = 3;  typeSize = sizeof(GLfloat) * 3.f;  dataType = GL_FLOAT; break;
        case GL_FLOAT_VEC4: elements = 4;  typeSize = sizeof(GLfloat) * 4.f;  dataType = GL_FLOAT; break;
        case GL_FLOAT_MAT3: elements = 9;  typeSize = sizeof(GLfloat) * 9.f;  dataType = GL_FLOAT; break;
        case GL_FLOAT_MAT4: elements = 16; typeSize = sizeof(GLfloat) * 16.f; dataType = GL_FLOAT; break;
    }
    if (typeSize > 0)
    {
        m_Size      = size;
        m_Type      = type;
        m_TypeSize  = typeSize;
        m_DataType  = dataType;
        m_Elements  = elements;
        m_Dynamic   = dynamic;
        m_Attribute = 0;
        // Create GL buffers
        glGenBuffers(1, (GLuint *)&m_Vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
        glBufferData(GL_ARRAY_BUFFER, m_Size * m_TypeSize, data, m_Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        res = true;
    }
    else
        dry::Log(LogWarning, "[Vbo] Error creating VertexBufferObject with size %d", size);

    return true;
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
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
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
    glVertexAttribPointer(m_Attribute, m_Elements, m_DataType, GL_FALSE, 0, 0);
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
