//
//  Vbo.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

template <class T>
class Vbo
{
public:
                Vbo     () { m_Vbo = 0; m_Data = NULL; }
               ~Vbo     () { Free(); }
    
    bool        Init    (int size, bool dynamic, int elements, T const *data);
    void        Free    ();
    
    int         GetVbo  () const { return m_Vbo; }
    T          *GetData () { return m_Data; }

    void        Bind    (int attr, bool forceUpdate = false);
    void        Unbind  (int attr);

private:
    
    int         m_Elements;
    bool        m_Dynamic;
    int         m_Size;
    int         m_Vbo;
    T          *m_Data;
};

}
