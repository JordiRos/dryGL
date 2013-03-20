//
//  Texture.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Texture.h"
#include "Image.h"

using namespace dry;

    
//------------------------------------------------------------------------------------------------
// InitWithData
//
//------------------------------------------------------------------------------------------------
bool Texture::InitWithData(int width, int height, PixelFormat format, const void *data)
{
    Free();
    bool res = false;
    m_Width  = width;
    m_Height = height;
    m_Format = format;
    m_Target = GL_TEXTURE_2D;

	glGenTextures(1, (GLuint *)&m_Handle);
    if (m_Handle != -1)
    {
        int glFormat = GetGLFormat();
        glBindTexture  (m_Target, m_Handle);
        glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D   (m_Target, 0, glFormat, m_Width, m_Height, 0, glFormat, GL_UNSIGNED_BYTE, data);
        glBindTexture  (m_Target, 0);
        res = true;
    }
    else
        dry::Log(LOG_WARNING, "[dryTexture] Can't create texture with params: %d,%d / PixelFormat: %d", width, height, format);
    return res;
}


//------------------------------------------------------------------------------------------------
// InitWithImage
//
//------------------------------------------------------------------------------------------------
bool Texture::InitWithImage(const Image &img)
{
    return InitWithData(img.GetWidth(), img.GetHeight(), img.GetFormat(), img.GetData());
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Texture::Free()
{
    if (m_Handle != -1)
        glDeleteTextures(1, (GLuint *)&m_Handle);
    m_Handle = -1;
}


//------------------------------------------------------------------------------------------------
// Update
//
//------------------------------------------------------------------------------------------------
void Texture::Update(const void *data)
{
    int glFormat = GetGLFormat();

    glBindTexture(m_Target, m_Handle);
    glTexImage2D (m_Target, 0, glFormat, m_Width, m_Height, 0, glFormat, GL_UNSIGNED_BYTE, data);
    glBindTexture(m_Target, 0);
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void Texture::Bind(int uniform, int stage) const
{
    glBindTexture  (m_Target, m_Handle);
    glActiveTexture(GL_TEXTURE0 + stage);
    glUniform1i    (uniform, 0);
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void Texture::Unbind() const
{
    glBindTexture(m_Target, 0);
}


//------------------------------------------------------------------------------------------------
// GetGLFormat
//
//------------------------------------------------------------------------------------------------
int Texture::GetGLFormat() const
{
    switch (m_Format)
    {
        case PF_ALPHA:   return GL_ALPHA;
        case PF_RGB565:  return GL_RGB;
        case PF_RGB24:   return GL_RGB;
        case PF_ARGB32:  return GL_RGBA;
        case PF_UNKNOWN: return 0;
    }
    return 0;
}


//------------------------------------------------------------------------------------------------
// GetGLType
//
//------------------------------------------------------------------------------------------------
int Texture::GetGLType() const
{
    switch (m_Format)
    {
        case PF_ALPHA:   return GL_UNSIGNED_BYTE;
        case PF_RGB565:  return GL_UNSIGNED_BYTE;
        case PF_RGB24:   return GL_UNSIGNED_BYTE;
        case PF_ARGB32:  return GL_UNSIGNED_BYTE;
        case PF_UNKNOWN: return 0;
    }
    return 0;
}
