//
//  MaterialMeshBasic.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

#include "../src/graphics/Material.h"

namespace dry {
    
class MeshMaterial : public Material
{
public:
                    MeshMaterial            () { }
                   ~MeshMaterial            () { Free(); }
    
    virtual bool    Init                    (const char *vs, const char *fs);
    virtual void    Free                    ();
    
    // Attributes
//    Attribute      *GetAttrVertices         () { return m_AttrVertices; }
//    Attribute      *GetAttrTexCoords0       () { return m_AttrTexCoords0; }
//    Attribute      *GetAttrTexCoords1       () { return m_AttrTexCoords1; }
//    Attribute      *GetAttrTexCoords2       () { return m_AttrTexCoords2; }
//    Attribute      *GetAttrTexCoords3       () { return m_AttrTexCoords3; }
//    Attribute      *GetAttrNormals          () { return m_AttrNormals; }
//    Attribute      *GetAttrColors           () { return m_AttrColors; }
//    // Uniforms
//    Uniform        *GetUniformModel         () { return m_UniformModel; }
//    Uniform        *GetUniformView          () { return m_UniformView; }
//    Uniform        *GetUniformProjection    () { return m_UniformProjection; }
//    Uniform        *GetUniformTexture0      () { return m_UniformTexture0; }
//    Uniform        *GetUniformTexture1      () { return m_UniformTexture1; }
//    Uniform        *GetUniformTexture2      () { return m_UniformTexture2; }
//    Uniform        *GetUniformTexture3      () { return m_UniformTexture3; }
//    Uniform        *GetUniformTextureCube0  () { return m_UniformTextureCube0; }
//    Uniform        *GetUniformTextureCube1  () { return m_UniformTextureCube1; }
//    Uniform        *GetUniformTextureCube2  () { return m_UniformTextureCube2; }
//    Uniform        *GetUniformTextureCube3  () { return m_UniformTextureCube3; }

protected:
    
    // Attributes
//    Attribute      *m_AttrVertices;
//    Attribute      *m_AttrTexCoords0;
//    Attribute      *m_AttrTexCoords1;
//    Attribute      *m_AttrTexCoords2;
//    Attribute      *m_AttrTexCoords3;
//    Attribute      *m_AttrNormals;
//    Attribute      *m_AttrColors;
//    // Uniforms
//    Uniform        *m_UniformModel;
//    Uniform        *m_UniformView;
//    Uniform        *m_UniformProjection;
//    Uniform        *m_UniformTexture0;
//    Uniform        *m_UniformTexture1;
//    Uniform        *m_UniformTexture2;
//    Uniform        *m_UniformTexture3;
//    Uniform        *m_UniformTextureCube0;
//    Uniform        *m_UniformTextureCube1;
//    Uniform        *m_UniformTextureCube2;
//    Uniform        *m_UniformTextureCube3;
};
    
}
