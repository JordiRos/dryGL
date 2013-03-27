//
//  Geometry.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

class Geometry
{
public:
    struct Params
    {
        Params()
        {
            Faces      = 0;
            Vertices   = 0;
            TexCoords0 = 0;
            TexCoords1 = 0;
            TexCoords2 = 0;
            TexCoords3 = 0;
            Normals    = 0;
            Colors     = 0;
        }
        int     Faces;
        ushort  Vertices;
        ushort  TexCoords0;
        ushort  TexCoords1;
        ushort  TexCoords2;
        ushort  TexCoords3;
        ushort  Normals;
        ushort  Colors;
    };
    
    struct Face
    {
        ushort vtx[3];
        ushort uv0[3];
        ushort uv1[3];
        ushort uv2[3];
        ushort uv3[3];
        ushort nor[3];
        ushort col[3];
    };

public:
                        Geometry        () { }
                       ~Geometry        () { Free(); }

    bool                Init            (Params const &params);
    void                Free            ();

    vector<Face>       &GetFaces        ();
    vector<glm::vec3>  &GetVertices     ();
    vector<glm::vec2>  &GetTexCoords0   ();
    vector<glm::vec2>  &GetTexCoords1   ();
    vector<glm::vec2>  &GetTexCoords2   ();
    vector<glm::vec2>  &GetTexCoords3   ();
    vector<glm::vec3>  &GetNormals      ();
    vector<glm::vec4>  &GetColors       ();

protected:
    
    Params              m_Params;
    vector<Face>        m_Faces;
    vector<glm::vec3>   m_Vertices;
    vector<glm::vec2>   m_TexCoords0;
    vector<glm::vec2>   m_TexCoords1;
    vector<glm::vec2>   m_TexCoords2;
    vector<glm::vec2>   m_TexCoords3;
    vector<glm::vec3>   m_Normals;
    vector<glm::vec4>   m_Colors;
};
    
}
