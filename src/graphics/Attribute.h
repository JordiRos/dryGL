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

    bool            Init        (Shader *shader, string const &name, int size, DataType type, bool dynamic);
    bool            Init        (Shader *shader, int idx, int size, bool dynamic);
    void            Free        ();
    
    void            Update      (bool now);

    void            Bind        ();
    void            Unbind      ();
    
    void           *GetData     () { return m_Data; }
    string const   &GetName     () const { return m_Name; }

protected:

    int             m_Attribute;
    DataType        m_Type;
    int             m_Size;
    string          m_Name;
    bool            m_Update;
    Vbo             m_Vbo;
    uchar          *m_Data;
};
    
}
