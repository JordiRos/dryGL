//
//  Texture.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Texture.h"

using namespace dry;

    
//------------------------------------------------------------------------------------------------
// InitWithData
//
//------------------------------------------------------------------------------------------------
bool Texture::InitWithData(int width, int height, PixelFormat format, Texture::Params const &params, void const *data)
{
    Free();
    bool res = false;
    m_Width   = width;
    m_Height  = height;
    m_Format  = format;
    m_Params  = params;
    m_Target  = GL_TEXTURE_2D;
    m_Release = true;

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
        glTexImage2D   (m_Target, 0, glFormat, m_Width, m_Height, 0, glFormat, GL_UNSIGNED_BYTE, data);
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
bool Texture::InitWithHandle(int width, int height, PixelFormat format, int handle)
{
    m_Handle  = handle;
    m_Width   = width;
    m_Height  = height;
    m_Format  = format;
    m_Target  = GL_TEXTURE_2D;
    m_Release = false;

    return true;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Texture::Free()
{
    if (m_Release && m_Handle)
        glDeleteTextures(1, (GLuint *)&m_Handle);
    m_Handle = 0;
}


//------------------------------------------------------------------------------------------------
// Update
//
//------------------------------------------------------------------------------------------------
void Texture::Update(void const *data)
{
    int glFormat = GetGLFormat();

    glBindTexture(m_Target, m_Handle);
    glTexImage2D (m_Target, 0, glFormat, m_Width, m_Height, 0, glFormat, GL_UNSIGNED_BYTE, data);
    if (m_Params.Mipmaps) glGenerateMipmap(m_Target);
    glBindTexture(m_Target, 0);
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void Texture::Bind(int stage)
{
    glActiveTexture(GL_TEXTURE0 + stage);
    glBindTexture  (m_Target, m_Handle);
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void Texture::Unbind()
{
    glBindTexture(m_Target, 0);
}


//------------------------------------------------------------------------------------------------
// GetGLFormat
//
//------------------------------------------------------------------------------------------------
int Texture::GetGLFormat()
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
int Texture::GetGLType()
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
