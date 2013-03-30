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
                        Geometry            () { }
                       ~Geometry            () { Free(); }

    bool                Init                (Params const &params);
    void                Free                ();

    vector<Face>       &GetFaces            () { return m_Faces; }
    vector<glm::vec3>  &GetVertices         () { return m_Vertices; }
    vector<glm::vec2>  &GetTexCoords0       () { return m_TexCoords0; }
    vector<glm::vec2>  &GetTexCoords1       () { return m_TexCoords1; }
    vector<glm::vec2>  &GetTexCoords2       () { return m_TexCoords2; }
    vector<glm::vec2>  &GetTexCoords3       () { return m_TexCoords3; }
    vector<glm::vec3>  &GetNormals          () { return m_Normals; }
    vector<glm::vec4>  &GetColors           () { return m_Colors; }

    void                UpdateVertices      (bool update) { m_UpdateVertices   = update && m_Vertices.size  () > 0; }
    void                UpdateTexCoords0    (bool update) { m_UpdateTexCoords0 = update && m_TexCoords0.size() > 0; }
    void                UpdateTexCoords1    (bool update) { m_UpdateTexCoords1 = update && m_TexCoords1.size() > 0; }
    void                UpdateTexCoords2    (bool update) { m_UpdateTexCoords2 = update && m_TexCoords2.size() > 0; }
    void                UpdateTexCoords3    (bool update) { m_UpdateTexCoords3 = update && m_TexCoords3.size() > 0; }
    void                UpdateNormals       (bool update) { m_UpdateNormals    = update && m_Normals.size   () > 0; }
    void                UpdateColors        (bool update) { m_UpdateColors     = update && m_Colors.size    () > 0; }

    bool                GetUpdateVertices   () { return m_UpdateVertices;   }
    bool                GetUpdateTexCoords0 () { return m_UpdateTexCoords0; }
    bool                GetUpdateTexCoords1 () { return m_UpdateTexCoords1; }
    bool                GetUpdateTexCoords2 () { return m_UpdateTexCoords2; }
    bool                GetUpdateTexCoords3 () { return m_UpdateTexCoords3; }
    bool                GetUpdateNormals    () { return m_UpdateNormals;    }
    bool                GetUpdateColors     () { return m_UpdateColors;     }

protected:

    vector<Face>        m_Faces;
    vector<glm::vec3>   m_Vertices;
    vector<glm::vec2>   m_TexCoords0;
    vector<glm::vec2>   m_TexCoords1;
    vector<glm::vec2>   m_TexCoords2;
    vector<glm::vec2>   m_TexCoords3;
    vector<glm::vec3>   m_Normals;
    vector<glm::vec4>   m_Colors;
    bool                m_UpdateVertices;
    bool                m_UpdateTexCoords0;
    bool                m_UpdateTexCoords1;
    bool                m_UpdateTexCoords2;
    bool                m_UpdateTexCoords3;
    bool                m_UpdateNormals;
    bool                m_UpdateColors;
};

}
