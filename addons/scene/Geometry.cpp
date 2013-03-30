//
//  Mesh.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Scene.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Geometry::Init(Geometry::Params const &params)
{
    bool res = true;
    Free();

    m_Faces.resize(params.Faces);
    m_Vertices.resize(params.Vertices);
    m_TexCoords0.resize(params.TexCoords0);
    m_TexCoords1.resize(params.TexCoords1);
    m_TexCoords2.resize(params.TexCoords2);
    m_TexCoords3.resize(params.TexCoords3);
    m_Normals.resize(params.Normals);
    m_Colors.resize(params.Colors);
    
    // Updates
    UpdateVertices  (true);
    UpdateTexCoords0(true);
    UpdateTexCoords1(true);
    UpdateTexCoords2(true);
    UpdateTexCoords3(true);
    UpdateNormals   (true);
    UpdateColors    (true);

    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Geometry::Free()
{
    m_Faces.clear();
    m_Vertices.clear();
    m_TexCoords0.clear();
    m_TexCoords1.clear();
    m_TexCoords2.clear();
    m_TexCoords3.clear();
    m_Normals.clear();
    m_Colors.clear();
}
