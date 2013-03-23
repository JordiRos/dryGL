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
bool GeometryPlane::Init(float w, float h, glm::vec3 const &up)
{
    // Vertices
    glm::vec3 verticesX[] = {
        glm::vec3(0.0f, -1.0f * w, -1.0f * h),
        glm::vec3(0.0f,  1.0f * w, -1.0f * h),
        glm::vec3(0.0f,  1.0f * w,  1.0f * h),
        glm::vec3(0.0f, -1.0f * w,  1.0f * h),
    };
    glm::vec3 verticesY[] = {
        glm::vec3(-1.0f * w, 0.0f, -1.0f * h),
        glm::vec3( 1.0f * w, 0.0f, -1.0f * h),
        glm::vec3( 1.0f * w, 0.0f,  1.0f * h),
        glm::vec3(-1.0f * w, 0.0f,  1.0f * h),
    };
    glm::vec3 verticesZ[] = {
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

    glm::vec3 *vertices = verticesY;
    if (up.x > 0.f) vertices = verticesX;
    if (up.y > 0.f) vertices = verticesY;
    if (up.z > 0.f) vertices = verticesZ;
    if (up.x < 0.f || up.y < 0.f || up.z < 0.f)
    {
        for (int i = 0; i < 4; ++i)
        {
            vertices[i].x = -vertices[i].x;
            vertices[i].y = -vertices[i].y;
            vertices[i].z = -vertices[i].z;
        }
    }
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
