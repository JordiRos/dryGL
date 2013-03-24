//
//  Vbo.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

class Vbo
{
public:
                Vbo         () { m_Vbo = 0; }
               ~Vbo         () { Free(); }
    
    bool        Init        (void const *data, int size, int type, bool dynamic);
    void        Free        ();
    
    void        Update      (void const *data, int size, int offset);

    void        Bind        (int attribute);
    void        Unbind      ();
    
private:
    
    int         m_Vbo;
    int         m_Size;
    int         m_Type;
    int         m_TypeSize;
    int         m_DataType;
    int         m_Elements;
    bool        m_Dynamic;
    int         m_Attribute;
};

}
