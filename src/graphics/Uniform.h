//
//  Uniform.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

class Uniform
{
public:
                    Uniform () { m_Uniform = 0; }
                   ~Uniform () { Free(); }

    bool            Init    (int uniform, DataType type);
    void            Free    ();

    void            Bind    ();
    void            Unbind  ();

    // Update
    void            Update  (int              value) { m_Value.i   = value; }
    void            Update  (float            value) { m_Value.f   = value; }
    void            Update  (glm::vec2 const &value) { m_Value.v2  = value; }
    void            Update  (glm::vec3 const &value) { m_Value.v3  = value; }
    void            Update  (glm::vec4 const &value) { m_Value.v4  = value; }
    void            Update  (glm::mat2 const &value) { m_Value.m2  = value; }
    void            Update  (glm::mat3 const &value) { m_Value.m3  = value; }
    void            Update  (glm::mat4 const &value) { m_Value.m4  = value; }
    void            Update  (Texture     *tex,  int stage) { m_Value.tex.Set(tex, stage); }
    void            Update  (TextureCube *cube, int stage) { m_Value.cube.Set(cube, stage); }
    void            Update  (Fbo         *fbo,  int stage) { m_Value.fbo.Set(fbo, stage); }

public:

    struct Tex2D
    {
        Tex2D() { tex = NULL; stage = 0; }
        void Set(Texture *t, int s) { tex = t; stage = s; }
        Texture *tex;
        int      stage;
    };
    struct TexCube
    {
        TexCube() { tex = NULL; stage = 0; }
        void Set(TextureCube *t, int s) { tex = t; stage = s; }
        TextureCube *tex;
        int          stage;
    };
    struct TexFbo
    {
        TexFbo() { fbo = NULL; stage = 0; }
        void Set(Fbo *f, int s) { fbo = f; stage = s; }
        Fbo *fbo;
        int  stage;
    };
    
    union Var
    {
        Var() {}
        int         i;
        float       f;
        glm::vec2   v2;
        glm::vec3   v3;
        glm::vec4   v4;
        glm::mat2   m2;
        glm::mat3   m3;
        glm::mat4   m4;
        Tex2D       tex;
        TexCube     cube;
        TexFbo      fbo;
    };

protected:

    int             m_Uniform;
    DataType        m_Type;
    Var             m_Value;
};
    
}
