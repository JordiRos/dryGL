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
    
    bool        Init        (void const *data, int size, DataType type, bool dynamic);
    void        Free        ();
    
    void        Update      (void const *data, int size, int offset);

    void        Bind        (int attribute);
    void        Unbind      ();

    int         GetType     () { return m_Type; }
    int         GetSize     () { return m_Size; }
    int         GetGLType   () { return m_GLType; }

private:
    
    int         m_Vbo;
    int         m_Size;
    DataType    m_Type;
    int         m_TypeSize;
    int         m_Elements;
    int         m_GLType;
    bool        m_Dynamic;
    int         m_Attribute;
};

}
