//
//  Ibo.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

class Ibo
{
public:
                Ibo     () { m_Ibo = 0; }
               ~Ibo     () { Free(); }
    
    bool        Init    (void const *data, int size, int type, bool dynamic);
    void        Free    ();

    void        Bind    ();
    void        Unbind  ();

    void        Draw    (int primitive);
    
private:
    
    int         m_Ibo;
    int         m_Size;
    int         m_Type;
    int         m_TypeSize;
    int         m_DataType;
    bool        m_Dynamic;
};

}
