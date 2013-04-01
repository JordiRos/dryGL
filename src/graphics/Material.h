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
    virtual                ~Material        () { Free(); }

    virtual bool            Init            (Shader *shader);
    virtual void            Free            ();

    virtual void            Bind            ();
    virtual void            Unbind          ();
    
    Shader                 *GetShader       () { return m_Shader; }
    UniformInterface       *GetUniform      (string const &name) { return m_Shader->GetUniformByName(name); }
//    Attribute              *GetAttribute    (string const &name) { return NULL; }
    
protected:

    Shader                 *m_Shader;
};
    
}
