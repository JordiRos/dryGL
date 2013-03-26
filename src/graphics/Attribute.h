//
//  Attribute.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

class Attribute
{
public:
                    Attribute   () { m_Attribute = 0; m_Data = NULL; }
                   ~Attribute   () { Free(); }

    bool            Init        (int attribute, int size, DataType type, bool dynamic);
    void            Free        ();
    
    void            Update      (bool now);

    void            Bind        ();
    void            Unbind      ();
    
    void           *GetBuffer   () { return m_Data; }

protected:

    int             m_Attribute;
    DataType        m_Type;
    int             m_Size;
    bool            m_Update;
    Vbo             m_Vbo;
    uchar          *m_Data;
};
    
}
