//
//  QuadBatch.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

class QuadBatch
{
public:
            QuadBatch       () { m_Vertices = m_Indices = m_TexCoords = 0; }
           ~QuadBatch       () { Free(); }
    
    void    Init            ();
    void    Free            ();
    
    void    Draw            (Texture const *texture, Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h);
    void    Draw            (Fbo     const *fbo,     Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h);

private:
    
    void    Draw            (int texture, Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h);

private:
    
    int     m_Vertices;
    int     m_TexCoords;
    int     m_Indices;
};
    
}
