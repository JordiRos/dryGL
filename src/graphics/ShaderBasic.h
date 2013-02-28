//
//  ShaderBasic.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class Shader;

class ShaderBasic
{
public:
                    ShaderBasic     () { m_Shader = NULL; }
                   ~ShaderBasic     () { Free(); }

    bool            Init            ();
    void            Free            ();

    void            Begin           ();
    void            End             ();

    Shader         *GetShader       () { return m_Shader; }

private:

    Shader         *m_Shader;
};

}