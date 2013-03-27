//
//  Mesh.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Mesh.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Mesh::Init(Geometry *geometry, Material *material)
{
    bool res = true;
    
    m_Geometry         = geometry;
    m_Material         = material;
    m_UpdateVertices   = false;
    m_UpdateTexCoords0 = false;
    m_UpdateTexCoords1 = false;
    m_UpdateTexCoords2 = false;
    m_UpdateTexCoords3 = false;
    m_UpdateNormals    = false;
    m_UpdateColors     = false;
    m_UpdateIndices    = false;
    
    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Mesh::Free()
{
}


//------------------------------------------------------------------------------------------------
// Draw
//
//------------------------------------------------------------------------------------------------
void Mesh::Draw()
{
}
