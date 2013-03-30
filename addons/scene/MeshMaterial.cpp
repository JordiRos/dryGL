//
//  MaterialMeshBasic.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "MeshMaterial.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool MeshMaterial::Init(const char *vs, const char *fs)
{
    bool res = false;
    Free();
    
    Shader *shader = NEW Shader();
    if (shader->InitWithProgram(vs, fs))
    {
        if (Material::Init(shader))
        {
            // Attributes
            m_AttrVertices        = GetAttribute("Position");
            m_AttrTexCoords0      = GetAttribute("TexCoord0");
            m_AttrTexCoords1      = GetAttribute("TexCoord1");
            m_AttrTexCoords2      = GetAttribute("TexCoord2");
            m_AttrTexCoords3      = GetAttribute("TexCoord3");
            m_AttrNormals         = GetAttribute("Normal");
            m_AttrColors          = GetAttribute("Color");
            // Uniforms
            m_UniformModel        = GetUniform("Model");
            m_UniformView         = GetUniform("View");
            m_UniformProjection   = GetUniform("Projection");
            m_UniformTexture0     = GetUniform("Texture0");
            m_UniformTexture1     = GetUniform("Texture1");
            m_UniformTexture2     = GetUniform("Texture2");
            m_UniformTexture3     = GetUniform("Texture3");
            m_UniformTextureCube0 = GetUniform("TextureCube0");
            m_UniformTextureCube1 = GetUniform("TextureCube1");
            m_UniformTextureCube2 = GetUniform("TextureCube2");
            m_UniformTextureCube3 = GetUniform("TextureCube3");
            res = true;
        }
    }
    
    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void MeshMaterial::Free()
{
    // Attributes
    m_AttrVertices        = NULL;
    m_AttrTexCoords0      = NULL;
    m_AttrTexCoords1      = NULL;
    m_AttrTexCoords2      = NULL;
    m_AttrTexCoords3      = NULL;
    m_AttrNormals         = NULL;
    m_AttrColors          = NULL;
    // Uniforms
    m_UniformModel        = NULL;
    m_UniformView         = NULL;
    m_UniformProjection   = NULL;
    m_UniformTexture0     = NULL;
    m_UniformTexture1     = NULL;
    m_UniformTexture2     = NULL;
    m_UniformTexture3     = NULL;
    m_UniformTextureCube0 = NULL;
    m_UniformTextureCube1 = NULL;
    m_UniformTextureCube2 = NULL;
    m_UniformTextureCube3 = NULL;
    // Shader
    DISPOSE(m_Shader);
    Material::Free();
}
