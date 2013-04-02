//
//  GeometryUtils.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Scene.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// LoadObj
//
//------------------------------------------------------------------------------------------------
bool GeometryUtils::LoadObj(Geometry &geo, const std::string &file)
{
    bool res = false;
    dry::Log(LogWarning, "[GeometryUtils] Load geometry from file %s", file.c_str());
    FILE *f = fopen(file.c_str(), "r");
    if (f)
    {
        // Count data
        Geometry::Params params;
        fseek(f, 0, SEEK_SET);
        for (;;)
        {
            static char line[512];
            if (fscanf(f, "%s", line) != EOF)
            {
                if (strcmp(line, "v") == 0)
                    params.Vertices++;
                else if (strcmp(line, "vt") == 0)
                    params.TexCoords0++;
                else if (strcmp(line, "vn") == 0)
                    params.Normals++;
                else if (strcmp(line, "f") == 0)
                    params.Faces++;
            }
            else break;
        }

        // Useful data?
        if (params.Faces > 0 && params.Vertices > 0)
        {
            // Init geometry and read values
            dry::Log(LogInfo, "[GeometryUtils] Loading Geometry Obj with %d faces, %d vertices, %d normals", params.Faces, params.Vertices, params.Normals);
            // Geometry
            params.Colors = 1;
            geo.Init(params);
            std::vector<Geometry::Face> &faces      = geo.GetFaces     ();
            std::vector<glm::vec3>      &vertices   = geo.GetVertices  ();
            std::vector<glm::vec2>      &texcoords0 = geo.GetTexCoords0();
            std::vector<glm::vec3>      &normals    = geo.GetNormals   ();
            if (params.Faces      > 0) faces.clear();
            if (params.Vertices   > 0) vertices.clear();
            if (params.TexCoords0 > 0) texcoords0.clear();
            if (params.Normals    > 0) normals.clear();
            geo.GetColors()[0] = glm::vec4(1.f, 1.f, 1.f, 1.f);
            fseek(f, 0, SEEK_SET);
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
                        texcoords0.push_back(uv);
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
                        for (int i = 0; i < 3; i++)
                        {
                            face.vtx[i]--;
                            face.uv0[i]--;
                            face.nor[i]--;
                            face.col[i] = 0;
                        }
                        faces.push_back(face);
                    }
                }
                else break;
            }
            res = true;
        }
    }
    else
        dry::Log(LogWarning, "[GeometryUtils] Error loading Geometry OBJ from file %s", file.c_str());
    return res;
}
