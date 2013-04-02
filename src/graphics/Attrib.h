//
//  Attrib.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_GRAPHICS_ATTRIB_H_
#define DRY_GRAPHICS_ATTRIB_H_

namespace dry {

class Vbo;
    
class Attrib
{
public:
                Attrib      (int location, int gltype) : m_Location(location), m_GLType(gltype) {}
               ~Attrib      () {}
    
    void        SetVbo      (Vbo *vbo);

    void        Bind        ();
    void        Unbind      ();

protected:

    int         m_Location;
    int         m_GLType;
    Vbo        *m_Vbo;
};
    
}

#endif
