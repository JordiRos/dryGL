//
//  Ibo.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

template <class T>
class Ibo
{
public:
                Ibo     () { m_Ibo = 0; m_Data = NULL; }
               ~Ibo     () { Free(); }
    
    bool        Init    (int size, bool dynamic, T const *data);
    void        Free    ();

    void        Bind    ();
    void        Unbind  ();
    
    void        Draw    (int type);

    T          *GetData () { return m_Data; }

private:
    
    bool        m_Dynamic;
    int         m_Size;
    int         m_Ibo;
    T          *m_Data;
};

}
