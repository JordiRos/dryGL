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
                    Material        ();
                   ~Material        () { Free(); }

    bool            Init            (Shader *shader);
    void            Free            ();

    void            Bind            ();

protected:

    Shader         *m_Shader;
};
    
}
