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

public:
    
    DataVar         Value;

protected:

    int             m_Uniform;
    DataType        m_Type;
};
    
}
