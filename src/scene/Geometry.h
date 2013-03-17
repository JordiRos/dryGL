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
            Vertices   = 0;
            TexCoords0 = 0;
            TexCoords1 = 0;
            TexCoords2 = 0;
            TexCoords3 = 0;
            Normals    = 0;
            Colors     = 0;
            Indices    = 0;
            Dynamic    = false;
        }
        int  Vertices;
        int  TexCoords0;
        int  TexCoords1;
        int  TexCoords2;
        int  TexCoords3;
        int  Normals;
        int  Colors;
        int  Indices;
        bool Dynamic;
    };

public:
                    Geometry        ();
                   ~Geometry        () { Free(); }
    
    bool            Init            (Params const &params);
    void            Free            ();
    
    // Data
    Vbo<glm::vec3> *GetVertices     () { return &m_Vertices; }
    Vbo<glm::vec2> *GetTexCoords0   () { return &m_TexCoords0; }
    Vbo<glm::vec2> *GetTexCoords1   () { return &m_TexCoords1; }
    Vbo<glm::vec2> *GetTexCoords2   () { return &m_TexCoords2; }
    Vbo<glm::vec2> *GetTexCoords3   () { return &m_TexCoords3; }
    Vbo<glm::vec3> *GetNormals      () { return &m_Normals; }
    Vbo<glm::vec4> *GetColors       () { return &m_Colors; }
    Ibo<ushort>    *GetIndices      () { return &m_Indices; }

protected:
    
    Params          m_Params;
    Vbo<glm::vec3>  m_Vertices;
    Vbo<glm::vec2>  m_TexCoords0;
    Vbo<glm::vec2>  m_TexCoords1;
    Vbo<glm::vec2>  m_TexCoords2;
    Vbo<glm::vec2>  m_TexCoords3;
    Vbo<glm::vec3>  m_Normals;
    Vbo<glm::vec4>  m_Colors;
    Ibo<ushort>     m_Indices;
};
    
}
