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
template<class T>
bool Ibo<T>::Init(int size, bool dynamic, T const *data)
{
    m_Dynamic  = dynamic;
    m_Size = size * sizeof(T);
    m_Data = NEW_ARRAY(T, size);
    if (data)
        memcpy(m_Data, data, m_Size);
    else
        memset(m_Data, 0, m_Size);
    // Create GL buffers
    glGenBuffers(1, (GLuint *)&m_Ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Size, m_Data, GL_STATIC_DRAW);

    return true;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
template<class T>
void Ibo<T>::Free()
{
    if (m_Data)
    {
        glDeleteBuffers(1, (GLuint *)&m_Ibo);
        m_Ibo = 0;
        DISPOSE_ARRAY(m_Data);
    }
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
template<class T>
void Ibo<T>::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
template<class T>
void Ibo<T>::Unbind()
{
}


//------------------------------------------------------------------------------------------------
// Implicit Ibo definitions
//------------------------------------------------------------------------------------------------
template class dry::Ibo<ushort>;
template class dry::Ibo<uint>;
