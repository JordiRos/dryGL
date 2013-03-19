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
template<class T>
bool Vbo<T>::Init(int size, bool dynamic, int elements, T const *data)
{
    m_Elements = elements;
    m_Dynamic  = dynamic;
    m_Size = size;
    m_Data = NEW_ARRAY(T, m_Size);
    if (data)
        memcpy(m_Data, data, m_Size * sizeof(T));
    else
        memset(m_Data, 0, m_Size * sizeof(T));
    // Create GL buffers
    glGenBuffers(1, (GLuint *)&m_Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    glBufferData(GL_ARRAY_BUFFER, m_Size, m_Data, m_Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    return true;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
template<class T>
void Vbo<T>::Free()
{
    if (m_Data)
    {
        glDeleteBuffers(1, (GLuint *)&m_Vbo);
        m_Vbo = 0;
        DISPOSE_ARRAY(m_Data);
    }
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
template<class T>
void Vbo<T>::Bind(int attr, bool forceUpdate)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
    if (m_Dynamic || forceUpdate)
        glBufferData(GL_ARRAY_BUFFER, m_Size, m_Data, m_Dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    // Send to attribute
    glEnableVertexAttribArray(attr);
    glVertexAttribPointer(attr, m_Elements, GL_FLOAT, GL_FALSE, 0, 0);
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
template<class T>
void Vbo<T>::Unbind(int attr)
{
    // Clear attribute
    glEnableVertexAttribArray(attr);
}


//------------------------------------------------------------------------------------------------
// Implicit Vbo definitions
//------------------------------------------------------------------------------------------------
template class dry::Vbo<float>;
template class dry::Vbo<glm::vec2>;
template class dry::Vbo<glm::vec3>;
template class dry::Vbo<glm::vec4>;
template class dry::Vbo<glm::mat4>;
template class dry::Vbo<dry::Colorf>;
