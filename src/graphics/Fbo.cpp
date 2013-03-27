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
bool Fbo::Init(Renderer *renderer, Fbo::Params const &params)
{
    m_Renderer   = renderer;
    m_Params     = params;
    m_FboDefault = 0;
    m_Target     = GL_TEXTURE_2D;
    
    // Create FBO
    glGenFramebuffers (1, (GLuint *)&m_Fbo);
    glGenTextures     (1, (GLuint *)&m_FboColor);
    glGenRenderbuffers(1, (GLuint *)&m_FboDepth);

    // Create color texture
    glBindTexture  (m_Target, m_FboColor);
    glTexParameteri(m_Target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(m_Target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(m_Target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(m_Target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D   (m_Target, 0, GL_RGBA, m_Params.Width, m_Params.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    // Create depth texture
    glBindRenderbuffer   (GL_RENDERBUFFER, m_FboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24_OES, m_Params.Width, m_Params.Height);

    // FrameBuffer
	glBindFramebuffer    (GL_FRAMEBUFFER, m_Fbo);
    
    // Attach
    glFramebufferTexture2D   (GL_FRAMEBUFFER,  GL_COLOR_ATTACHMENT0, m_Target,        m_FboColor, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,  GL_DEPTH_ATTACHMENT,  GL_RENDERBUFFER, m_FboDepth);
    
    // Check status
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        dry::Log(LogWarning, "[Fbo] Error creating FrameBuffer: %d,%d", m_Params.Width, m_Params.Height);
    
    // Clear
	glBindTexture    (GL_TEXTURE_2D,  0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Create textures
    m_TextureColor.InitWithHandle(m_Params.Width, m_Params.Height, PixelFormatArgb32, m_FboColor);
    m_TextureDepth.InitWithHandle(m_Params.Width, m_Params.Height, PixelFormatArgb32, m_FboDepth);
    
    return true;
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
    if (!m_FboDefault)
    {
        m_ViewportDefault = m_Renderer->GetViewport();
        glGetIntegerv    (GL_FRAMEBUFFER_BINDING, (GLint *)&m_FboDefault);
        glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo);
        m_Renderer->SetViewport(0,0, m_Params.Width,m_Params.Height);
    }
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void Fbo::Unbind()
{
    if (m_FboDefault)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FboDefault);
        m_Renderer->SetViewport(m_ViewportDefault.x, m_ViewportDefault.y, m_ViewportDefault.z, m_ViewportDefault.w);
        m_FboDefault = 0;
    }
}
