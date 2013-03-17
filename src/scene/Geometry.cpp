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
    
    // Vertices
    if (m_Params.Vertices > 0)
        m_Vertices.Init(m_Params.Vertices, m_Params.Dynamic, 3, NULL);
    // TexCoords0
    if (m_Params.TexCoords0 > 0)
        m_TexCoords0.Init(m_Params.TexCoords0, m_Params.Dynamic, 2, NULL);
    // TexCoords1
    if (m_Params.TexCoords1 > 0)
        m_TexCoords1.Init(m_Params.TexCoords1, m_Params.Dynamic, 2, NULL);
    // TexCoords2
    if (m_Params.TexCoords2 > 0)
        m_TexCoords2.Init(m_Params.TexCoords2, m_Params.Dynamic, 2, NULL);
    // TexCoords3
    if (m_Params.TexCoords3 > 0)
        m_TexCoords3.Init(m_Params.TexCoords3, m_Params.Dynamic, 2, NULL);
    // Normals
    if (m_Params.Normals > 0)
        m_Normals.Init(m_Params.Normals, m_Params.Dynamic, 3, NULL);
    // Colors
    if (m_Params.Colors > 0)
        m_Colors.Init(m_Params.Colors, m_Params.Dynamic, 4, NULL);
    // Indices
    if (m_Params.Indices > 0)
        m_Indices.Init(m_Params.Indices, m_Params.Dynamic, NULL);
    
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
