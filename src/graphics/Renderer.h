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
    void            SetClearColor   (glm::vec4 const &color, float depth, int stencil);
    void            SetBlendMode    (BlendMode blend);
    
private:
    
    glm::vec4       m_ClearColor;
    float           m_ClearDepth;
    float           m_ClearStencil;
    BlendMode       m_BlendMode;
};

}
