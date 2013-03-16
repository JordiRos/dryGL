//
//  Fbo.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

class Fbo
{
public:
    struct Params
    {
        int  Width;
        int  Height;
    };
    
public:
            Fbo             () { m_Fbo = m_FboColor = m_FboDepth = 0; }
           ~Fbo             () { Free(); }
    
    bool    Init            (Params const &params);
    void    Free            ();
    
    void    Bind            ();
    void    Unbind          ();
    
    int     GetFboColor     () const { return m_FboColor; }
    int     GetFboDepth     () const { return m_FboDepth; }

    void    BindFboColor    (int uniform = 0, int stage = 0) const;
    void    UnbindFboColor  () const;
    void    BindFboDepth    (int uniform = 0, int stage = 0) const;
    void    UnbindFboDepth  () const;
    
private:
    
    Params  m_Params;
    int     m_Target;
    int     m_Fbo;
    int     m_FboColor;
    int     m_FboDepth;
    int     m_FboDefault;
};
    
}
