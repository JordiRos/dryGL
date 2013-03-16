//
//  Renderer.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class Renderer
{
public:

    void            Init        ();
    
    void            Begin       ();
    void            End         ();

    void            Clear       (int bits, Colorf const &color, float depth = 0.f, int stencil = 0);
                                 
private:
                                 
};

}
