//
//  GeometryPlane.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "GeometryPlane.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool GeometryPlane::Init(float w, float h, glm::mat4 const &lookat)
{
    // Vertices
    glm::vec3 vertices[] = {
        glm::vec3(-1.0f * w, -1.0f * h, 0.0f),
        glm::vec3( 1.0f * w, -1.0f * h, 0.0f),
        glm::vec3( 1.0f * w,  1.0f * h, 0.0f),
        glm::vec3(-1.0f * w,  1.0f * h, 0.0f),
    };
    // TexCoords
    glm::vec2 texcoords[] = {
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 0.0f),
    };
    // Indices
    GLushort indices[] = {
        0,  1,  2,
        2,  3,  0,
    };
    
    // Create geometry buffers
    Geometry::Params params;
    params.NumIndices  = 6;
    params.NumVertices = 4;
    params.Indices     = indices;
    params.Vertices    = vertices;
    params.TexCoords0  = texcoords;
    params.Flags       = Geometry::FL_TEXCOORDS0 | Geometry::FL_COLORS | Geometry::FL_NORMALS;
    Geometry::Init(params);
    
    return true;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void GeometryPlane::Free()
{
}
