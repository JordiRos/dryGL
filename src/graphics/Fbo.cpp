//
//  Fbo.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Fbo.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Fbo::Init(Fbo::Params const &params)
{
    bool res = false;
    m_FboDefault = -1;
    m_Target = GL_TEXTURE_2D;
    
    // Create FBO
    glGenFramebuffers (1, (GLuint *)&m_Fbo);
    glGenTextures     (1, (GLuint *)&m_FboColor);
    glGenRenderbuffers(1, (GLuint *)&m_FboDepth);

    // Bind
    Bind();

    // Create color texture
    glBindTexture(m_Target, m_FboColor);
    glTexImage2D (m_Target,
                  0,
                  GL_RGBA,
                  m_Params.Width, m_Params.Height,
                  0,
                  GL_RGBA,
                  GL_UNSIGNED_BYTE,
                  NULL);

    glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Create depth texture
    glBindRenderbuffer   (GL_RENDERBUFFER, m_FboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_Params.Width, m_Params.Height);

    // Attach
    glFramebufferTexture2D   (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_Target,        m_FboColor, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_RENDERBUFFER, m_FboDepth);
    
    // Unbind
    Unbind();
    
    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Fbo::Free()
{
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void Fbo::Bind()
{
    if (m_FboDefault == -1)
    {
        glGetIntegerv    (GL_FRAMEBUFFER_BINDING, (GLint *)&m_FboDefault);
        glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
    }
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void Fbo::Unbind()
{
    if (m_FboDefault != -1)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FboDefault);
        m_FboDefault = -1;
    }
}


//------------------------------------------------------------------------------------------------
// BindFboColor
//
//------------------------------------------------------------------------------------------------
void Fbo::BindFboColor() const
{
    glBindTexture(m_Target, m_FboColor);
}


//------------------------------------------------------------------------------------------------
// UnbindFboColor
//
//------------------------------------------------------------------------------------------------
void Fbo::UnbindFboColor() const
{
    glBindTexture(m_Target, 0);
}


//------------------------------------------------------------------------------------------------
// BindFboDepth
//
//------------------------------------------------------------------------------------------------
void Fbo::BindFboDepth() const
{
    glBindTexture(m_Target, m_FboDepth);
}


//------------------------------------------------------------------------------------------------
// UnbindFboDepth
//
//------------------------------------------------------------------------------------------------
void Fbo::UnbindFboDepth() const
{
    glBindTexture(m_Target, 0);
}
