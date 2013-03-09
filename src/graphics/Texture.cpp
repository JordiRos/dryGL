//
//  Texture.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Texture.h"
#include "Pixels.h"

using namespace dry;

    
//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Texture::Init(int width, int height, int format, int target)
{
    bool res = false;
    m_Width  = width;
    m_Height = height;
    m_Format = format;
    m_Target = target;
    
	glGenTextures(1, (GLuint *)&m_Handle);
    if (m_Handle != -1)
    {
        int glFormat = GetGLFormat();
        glBindTexture  (m_Target, m_Handle);
        glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D (m_Target, 0, glFormat, m_Width, m_Height, 0, glFormat, GL_UNSIGNED_BYTE, 0);
        glBindTexture(m_Target, 0);
        res = true;
    }
    else
        dry::Log("[dryTexture] Can't create texture with params: %d,%d (%d)", width, height, format);
    return res;
}


//------------------------------------------------------------------------------------------------
// InitWithDatanit
//
//------------------------------------------------------------------------------------------------
bool Texture::InitWithData(int width, int height, int format, int target, const void *data)
{
    Free();
    bool res = false;
    if (Init(width, height, format, target))
    {
        if (data)
            Update(data);
        res = true;
    }
    return res;
}


//------------------------------------------------------------------------------------------------
// InitWithPixels
//
//------------------------------------------------------------------------------------------------
bool Texture::InitWithPixels(const Pixels &pixels)
{
    Free();
    bool res = false;
    if (Init(pixels.GetWidth(), pixels.GetHeight(), pixels.GetFormat(), GL_TEXTURE_2D))
    {
        Update(pixels.GetData());
        res = true;
    }
    return res;
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
void Texture::Bind(int stage)
{
    glActiveTexture(GL_TEXTURE0 + stage);
    //glEnable(m_Target);
    glBindTexture(m_Target, m_Handle);
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void Texture::Unbind()
{
	//glDisable(m_Target);
}


//------------------------------------------------------------------------------------------------
// GetGLFormat
//
//------------------------------------------------------------------------------------------------
int Texture::GetGLFormat() const
{
    switch (m_Format)
    {
        case DRY_FMT_ALPHA:  return GL_ALPHA;
        case DRY_FMT_RGB565: return GL_RGB;
        case DRY_FMT_RGB24:  return GL_RGB;
        case DRY_FMT_RGBA32: return GL_RGBA;
    }
    return -1;
}


//------------------------------------------------------------------------------------------------
// GetGLType
//
//------------------------------------------------------------------------------------------------
int Texture::GetGLType() const
{
    switch (m_Format)
    {
        case DRY_FMT_ALPHA:  return GL_UNSIGNED_BYTE;
        case DRY_FMT_RGB565: return GL_UNSIGNED_BYTE;
        case DRY_FMT_RGB24:  return GL_UNSIGNED_BYTE;
        case DRY_FMT_RGBA32: return GL_UNSIGNED_BYTE;
    }
    return -1;
}
