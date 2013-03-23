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
    enum Flags
    {
        FL_TEXCOORDS0 = 1<<0,
        FL_TEXCOORDS1 = 1<<1,
        FL_TEXCOORDS2 = 1<<2,
        FL_TEXCOORDS3 = 1<<3,
        FL_COLORS     = 1<<4,
        FL_NORMALS    = 1<<5,
        FL_TANGENTS   = 1<<6,
    };
    struct Params
    {
        Params()
        {
            NumIndices  = 0;
            NumVertices = 0;
            Flags       = 0;
            Dynamic     = false;
            Indices     = NULL;
            Vertices    = NULL;
        }
        int         NumVertices;
        int         NumIndices;
        int         Flags;
        bool        Dynamic;
        ushort     *Indices;
        glm::vec3  *Vertices;
        glm::vec2  *TexCoords0;
        glm::vec2  *TexCoords1;
        glm::vec2  *TexCoords2;
        glm::vec2  *TexCoords3;
        glm::vec3  *Normals;
        glm::vec3  *Tangents;
        glm::vec4  *Colors;
    };

public:
                    Geometry        ();
                   ~Geometry        () { Free(); }
    
    bool            Init            (Params const &params);
    void            Free            ();
    
    // Data
    Ibo<ushort>    *GetIndices      () { return &m_Indices; }
    Vbo<glm::vec3> *GetVertices     () { return &m_Vertices; }
    Vbo<glm::vec2> *GetTexCoords0   () { return &m_TexCoords0; }
    Vbo<glm::vec2> *GetTexCoords1   () { return &m_TexCoords1; }
    Vbo<glm::vec2> *GetTexCoords2   () { return &m_TexCoords2; }
    Vbo<glm::vec2> *GetTexCoords3   () { return &m_TexCoords3; }
    Vbo<glm::vec3> *GetNormals      () { return &m_Normals; }
    Vbo<glm::vec3> *GetTangents     () { return &m_Tangents; }
    Vbo<glm::vec4> *GetColors       () { return &m_Colors; }

protected:
    
    Params          m_Params;
    Ibo<ushort>     m_Indices;
    Vbo<glm::vec3>  m_Vertices;
    Vbo<glm::vec2>  m_TexCoords0;
    Vbo<glm::vec2>  m_TexCoords1;
    Vbo<glm::vec2>  m_TexCoords2;
    Vbo<glm::vec2>  m_TexCoords3;
    Vbo<glm::vec3>  m_Normals;
    Vbo<glm::vec3>  m_Tangents;
    Vbo<glm::vec4>  m_Colors;
};
    
}
