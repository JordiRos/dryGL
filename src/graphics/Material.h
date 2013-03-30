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
    Uniform                *GetUniform      (string const &name) { map<string,Uniform   *>::iterator iter = m_Uniforms  .find(name); return (iter != m_Uniforms  .end()) ? iter->second : NULL; }
    Attribute              *GetAttribute    (string const &name) { map<string,Attribute *>::iterator iter = m_Attributes.find(name); return (iter != m_Attributes.end()) ? iter->second : NULL; }
    
protected:

    Shader                 *m_Shader;
    map<string,Uniform *>   m_Uniforms;
    map<string,Attribute *> m_Attributes;
};
    
}
