//
//  Mesh.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Geometry.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Constructor
//
//------------------------------------------------------------------------------------------------
Geometry::Geometry()
{
}


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Geometry::Init(Geometry::Params const &params)
{
    bool res = true;
    m_Params = params;
    
    /*
    // Vertices
    m_Vertices.Init(m_Params.NumVertices, m_Params.Dynamic, 3, params.Vertices);
    m_Indices.Init(m_Params.NumIndices, m_Params.Dynamic, params.Indices);
    // TexCoords0
    if (m_Params.Flags & FL_TEXCOORDS0)
        m_TexCoords0.Init(m_Params.NumVertices, m_Params.Dynamic, 2, params.TexCoords0);
    // TexCoords1
    if (m_Params.Flags & FL_TEXCOORDS1)
        m_TexCoords1.Init(m_Params.NumVertices, m_Params.Dynamic, 2, params.TexCoords1);
    // TexCoords2
    if (m_Params.Flags & FL_TEXCOORDS2)
        m_TexCoords2.Init(m_Params.NumVertices, m_Params.Dynamic, 2, params.TexCoords2);
    // TexCoords3
    if (m_Params.Flags & FL_TEXCOORDS3)
        m_TexCoords3.Init(m_Params.NumVertices, m_Params.Dynamic, 2, params.TexCoords3);
    // Normals
    if (m_Params.Flags & FL_NORMALS)
        m_Normals.Init(m_Params.NumVertices, m_Params.Dynamic, 3, params.Normals);
    // Tangents
    if (m_Params.Flags & FL_TANGENTS)
        m_Tangents.Init(m_Params.NumVertices, m_Params.Dynamic, 3, params.Tangents);
    // Colors
    if (m_Params.Flags & FL_COLORS)
        m_Colors.Init(m_Params.NumVertices, m_Params.Dynamic, 4, params.Colors);
     */
    
    // TexCoords0    
    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Geometry::Free()
{
}
