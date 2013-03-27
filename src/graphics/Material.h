//
//  Material.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class Material
{
public:
                            Material        () { m_Shader = NULL; }
                           ~Material        () { Free(); }

    bool                    Init            (Shader *shader);
    void                    Free            ();

    void                    Bind            ();
    
    Uniform                *GetUniform      (string const &name) { return m_Uniforms[name]; }
    Attribute              *GetAttribute    (string const &name) { return m_Attributes[name]; }
    
protected:

    Shader                 *m_Shader;
    map<string,Uniform *>   m_Uniforms;
    map<string,Attribute *> m_Attributes;
};
    
}
