//
//  TextureCube.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "TextureCube.h"

using namespace dry;

    
//------------------------------------------------------------------------------------------------
// InitWithData
//
//------------------------------------------------------------------------------------------------
bool TextureCube::InitWithData(int width, int height, PixelFormat format, TextureCube::Params const &params, void const **data)
{
    Free();
    bool res = false;
    m_Width  = width;
    m_Height = height;
    m_Format = format;
    m_Params = params;
    m_Target = GL_TEXTURE_CUBE_MAP;

	glGenTextures(1, (GLuint *)&m_Handle);
    if (m_Handle != -1)
    {
        int minf = 0;
        int magf = 0;
        if (m_Params.Mipmaps)
        {
            minf = m_Params.Bilinear ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR_MIPMAP_NEAREST;
            magf = GL_LINEAR_MIPMAP_NEAREST;
        }
        else
        {
            minf = m_Params.Bilinear ? GL_LINEAR : GL_NEAREST;
            magf = GL_NEAREST;
        }
        int glFormat = GetGLFormat();
        glBindTexture  (m_Target, m_Handle);
        glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, minf);
        glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, magf);
        glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, GL_REPEAT);
        for (int i = 0; i < 6; ++i)
            glTexImage2D((GLenum)(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i), 0, glFormat, m_Width, m_Height, 0, glFormat, GL_UNSIGNED_BYTE, data ? data[i] : NULL);
        if (m_Params.Mipmaps) glGenerateMipmap(m_Target);
        glBindTexture  (m_Target, 0);
        res = true;
    }
    else
        dry::Log(LogError, "[dryTexture] Can't create texture with params: %d,%d / PixelFormat: %d", width, height, format);
    return res;
}


//------------------------------------------------------------------------------------------------
// InitWithHandle
//
//------------------------------------------------------------------------------------------------
bool TextureCube::InitWithHandle(int width, int height, PixelFormat format, int handle)
{
    m_Handle  = handle;
    m_Width   = width;
    m_Height  = height;
    m_Format  = format;
    m_Target  = GL_TEXTURE_CUBE_MAP;
    m_Release = false;
    
    return true;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void TextureCube::Free()
{
    if (m_Release && m_Handle)
        glDeleteTextures(1, (GLuint *)&m_Handle);
    m_Handle = 0;
}


//------------------------------------------------------------------------------------------------
// Update
//
//------------------------------------------------------------------------------------------------
void TextureCube::Update(TextureCubeSide side, void const *data)
{
    int glFormat = GetGLFormat();

    glBindTexture(m_Target, m_Handle);
    glTexImage2D ((GLenum)(GL_TEXTURE_CUBE_MAP_POSITIVE_X + side), 0, glFormat, m_Width, m_Height, 0, glFormat, GL_UNSIGNED_BYTE, data);
    if (m_Params.Mipmaps) glGenerateMipmap(m_Target);
    glBindTexture(m_Target, 0);
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void TextureCube::Bind(int stage) const
{
    glActiveTexture(GL_TEXTURE0 + stage);
    glBindTexture  (m_Target, m_Handle);
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void TextureCube::Unbind() const
{
    glBindTexture(m_Target, 0);
}


//------------------------------------------------------------------------------------------------
// GetGLFormat
//
//------------------------------------------------------------------------------------------------
int TextureCube::GetGLFormat() const
{
    switch (m_Format)
    {
        case PixelFormatAlpha:   return GL_ALPHA;
        case PixelFormatRgb565:  return GL_RGB;
        case PixelFormatRgb24:   return GL_RGB;
        case PixelFormatArgb32:  return GL_RGBA;
        default:                 return 0;
    }
}


//------------------------------------------------------------------------------------------------
// GetGLType
//
//------------------------------------------------------------------------------------------------
int TextureCube::GetGLType() const
{
    switch (m_Format)
    {
        case PixelFormatAlpha:  return GL_UNSIGNED_BYTE;
        case PixelFormatRgb565: return GL_UNSIGNED_BYTE;
        case PixelFormatRgb24:  return GL_UNSIGNED_BYTE;
        case PixelFormatArgb32: return GL_UNSIGNED_BYTE;
        default:                return 0;
    }
}
