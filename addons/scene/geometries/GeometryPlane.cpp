//
//  GeometryPlane.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Scene.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// CreatePlane
//
//------------------------------------------------------------------------------------------------
bool GeometryUtils::CreatePlane(Geometry &geo, float w, float h, int segw, int segh, glm::vec3 const &up)
{
	float hw = w / 2.f;
	float hh = h / 2.f;
	float dw = w / segw;
	float dh = h / segh;
    
    // Create geometry buffers
    int nvertices = (segw+1) * (segh+1);
    int nfaces    = segw * segh * 2;
    Geometry::Params params;
    params.Faces      = nfaces;
    params.Vertices   = nvertices;
    params.TexCoords0 = nvertices;
    params.Normals    = 1;
    params.Colors     = nvertices;
    geo.Init(params);

    // Buffers
    std::vector<Geometry::Face> &faces      = geo.GetFaces     ();
    std::vector<glm::vec3>      &vertices   = geo.GetVertices  ();
    std::vector<glm::vec2>      &texcoords0 = geo.GetTexCoords0();
    std::vector<glm::vec3>      &normals    = geo.GetNormals   ();
    std::vector<glm::vec4>      &colors     = geo.GetColors    ();
    
    // Normals
    normals[0] = up;
    
    // Vertices/TexCoords/Colors
    int f = 0;
    int v = 0;
    for (int i = 0; i <= segh; i++)
    {
        for (int j = 0; j <= segw; j++)
        {
			float x = j * dw - hw;
			float y = i * dh - hh;
            glm::vec3 vec;
            glm::vec2 tex;
            glm::vec4 col = glm::vec4(1.f, 1.f, 1.f, 1.f);
            // Vertices
            if      (up.x != 0) { vec = glm::vec3( 0, y,-x * up.x); tex = glm::vec2((float)j / segw, (float)(i) / segh); }
            else if (up.y != 0) { vec = glm::vec3( x, 0,-y * up.y); tex = glm::vec2((float)j / segw, (float)(i) / segh); }
            else if (up.z != 0) { vec = glm::vec3( x * up.z, y, 0); tex = glm::vec2((float)j / segw, (float)(i) / segh); }
            vertices  [v] = vec;
            texcoords0[v] = tex;
            colors    [v] = col;
            // Face
            if (i < segh && j < segw)
            {
                int i0, i1, i2;
                int f0 =  j      + (segw+1) * i;
                int f1 = (j + 1) + (segw+1) * i;
                int f2 = (j + 1) + (segw+1) * (i + 1);
                int f3 =  j      + (segw+1) * (i + 1);
                // Face 0
                i0 = f0; i1 = f2; i2 = f1;
                faces[f].vtx[0] = i0; faces[f].vtx[1] = i2; faces[f].vtx[2] = i1;
                faces[f].uv0[0] = i0; faces[f].uv0[1] = i2; faces[f].uv0[2] = i1;
                faces[f].nor[0] = 0;  faces[f].nor[1] = 0;  faces[f].nor[2] = 0;
                faces[f].col[0] = i0; faces[f].col[1] = i2; faces[f].col[2] = i1;
                f++;
                // Face 1
                i0 = f0; i1 = f3; i2 = f2;
                faces[f].vtx[0] = i0; faces[f].vtx[1] = i2; faces[f].vtx[2] = i1;
                faces[f].uv0[0] = i0; faces[f].uv0[1] = i2; faces[f].uv0[2] = i1;
                faces[f].nor[0] = 0;  faces[f].nor[1] = 0;  faces[f].nor[2] = 0;
                faces[f].col[0] = i0; faces[f].col[1] = i2; faces[f].col[2] = i1;
                f++;
            }
            v++;
        }
	}
    return true;
}
