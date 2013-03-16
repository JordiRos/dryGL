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
                    QuadBatch       () { m_Indices = 0; }
                   ~QuadBatch       () { Free(); }
    
    void            Init            ();
    void            Free            ();
    
    void            Draw            (Texture const *texture, Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h);
    void            Draw            (Fbo     const *fbo,     Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h);

private:
    
    void            Draw            (Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h);

private:
    
    Vbo<float>  m_Vertices;
    Vbo<float>  m_TexCoords;
    int             m_Indices;
};

}
