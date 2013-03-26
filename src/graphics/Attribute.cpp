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
bool Attribute::Init(int attribute, int size, DataType type, bool dynamic)
{
    bool res = false;
    if (GetDataTypeAttribute(type))
    {
        m_Attribute = attribute;
        m_Type      = type;
        m_Size      = size;
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
    if (m_Data)
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
