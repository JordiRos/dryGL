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
                    Renderer        ();
    
    void            Begin           ();
    void            End             ();

    void            Clear           (bool color, bool depth, bool stencil);
    
    void            SetViewport     (int x, int y, int w, int h);
    void            SetClearColor   (Colorf const &color, float depth, int stencil);
    void            SetBlendMode    (BlendMode blend);
    
private:
    
    Colorf          m_ClearColor;
    float           m_ClearDepth;
    float           m_ClearStencil;
    BlendMode       m_BlendMode;
};

}
