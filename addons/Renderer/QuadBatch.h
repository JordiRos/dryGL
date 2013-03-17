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
                    QuadBatch       () { }
                   ~QuadBatch       () { Free(); }
    
    void            Init            ();
    void            Free            ();
    
    void            Draw            (Texture const *texture, Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h);
    void            Draw            (Fbo     const *fbo,     Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h);

private:
    
    void            Draw            (Camera const *camera, Shader *shader, glm::mat4 const &transform, float x, float y, float w, float h);

private:
    
    Vbo<glm::vec3>  m_Vertices;
    Vbo<glm::vec2>  m_TexCoords;
    Ibo<ushort>     m_Indices;
};

}
