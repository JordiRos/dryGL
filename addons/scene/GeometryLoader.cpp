//
//  GeometryLoader.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Geometry.h"
#include "GeometryLoader.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool GeometryLoader::LoadGeometry(Geometry &geo, string const &file)
{
    bool res = false;
    dry::Log(LogWarning, "[GeometryLoader] Load geometry from file %s", file.c_str());
    FILE *f = fopen(file.c_str(), "r");
    if (f)
    {
        vector<glm::vec3>       vertices;
        vector<glm::vec2>       uvs;
        vector<glm::vec3>       normals;
        vector<Geometry::Face>  faces;
        for (;;)
        {
            static char line[512];
            if (fscanf(f, "%s", line) != EOF)
            {
                if (strcmp(line, "v") == 0)
                {
                    // Vertex
                    glm::vec3 vertex;
                    fscanf(f, "%f %f %f", &vertex.x, &vertex.y, &vertex.z);
                    vertices.push_back(vertex);
                }
                else if (strcmp(line, "vt") == 0)
                {
                    // Uv
                    glm::vec2 uv;
                    fscanf(f, "%f %f", &uv.x, &uv.y);
                    uvs.push_back(uv);
                }
                else if (strcmp(line, "vn") == 0)
                {
                    // Normals
                    glm::vec3 normal;
                    fscanf(f, "%f %f", &normal.x, &normal.y);
                    normals.push_back(normal);
                }
                else if (strcmp(line, "f") == 0)
                {
                    // Faces (only triangles)
                    Geometry::Face face;
                    fscanf(f, "%hu/%hu/%hu %hu/%hu/%hu %hu/%hu/%hu", &face.vtx[0],&face.uv0[0],&face.nor[0], &face.vtx[1],&face.uv0[1],&face.nor[1], &face.vtx[2],&face.uv0[2],&face.nor[2]);
                    faces.push_back(face);
                }
            }
            else break;
        }
        
        // Data ok?
        if (vertices.size() > 0 && faces.size() > 0)
        {
            Geometry::Params params;
            params.Faces      = faces.size();
            params.Vertices   = vertices.size();
            params.TexCoords0 = uvs.size();
            params.Normals    = normals.size();
            geo.Init(params);
            res = true;
        }
    }
    else
        dry::Log(LogWarning, "[GeometryLoader] Error loading geometry from file %s", file.c_str());
    return res;
}
