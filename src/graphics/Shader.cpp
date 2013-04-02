//
//  Shader.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Shader.h"
#include "Uniform.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Shader::Init(const char *vertex, const char *fragment)
{
    bool res = true;
    Free();
    
    int result;
    
    // Create Vertex
    m_Vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource (m_Vertex, 1, (GLchar const **)&vertex, NULL);
    glCompileShader(m_Vertex);
    glGetShaderiv  (m_Vertex, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        LogShaderError(m_Vertex, "vertex shader");
        res = false;
    }
    
    // Create Fragment
    m_Fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource (m_Fragment, 1, (GLchar const **)&fragment, NULL);
    glCompileShader(m_Fragment);
    glGetShaderiv  (m_Fragment, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        LogShaderError(m_Fragment, "fragment shader");
        res = false;
    }
    
    // Create Program
    if (res)
    {
        m_Program = glCreateProgram();
        glAttachShader(m_Program, m_Vertex);
        glAttachShader(m_Program, m_Fragment);
        glLinkProgram (m_Program);
        glGetProgramiv(m_Program, GL_LINK_STATUS, &result);
        if (result == GL_FALSE)
        {
            LogProgramError(m_Program, "program");
            res = false;
        }
        else
        {
            LoadUniforms();
            LoadAttribs ();
        }
    }

    // All ok?
    if (!res)
        Free();
    
    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Shader::Free()
{
    if (m_Vertex   != -1) glDeleteShader(m_Vertex);
    if (m_Fragment != -1) glDeleteShader(m_Fragment);
    if (m_Program  != -1) glDeleteProgram(m_Program);
    for (auto it = m_Uniforms.begin(); it != m_Uniforms.end(); ++it)
        DISPOSE(it->second);
    for (auto it = m_Attribs.begin(); it != m_Attribs.end(); ++it)
        DISPOSE(it->second);
    m_Vertex   = -1;
    m_Fragment = -1;
    m_Program  = -1;
    m_Uniforms.clear();
    m_Attribs.clear();
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void Shader::Bind()
{
    glUseProgram(m_Program);
    // Uniforms
	for (auto it = m_Uniforms.begin(); it != m_Uniforms.end(); ++it)
		it->second->Bind();
    // Attribs
	for (auto it = m_Attribs.begin(); it != m_Attribs.end(); ++it)
		it->second->Bind();
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void Shader::Unbind()
{
    // Attribs
	for (auto it = m_Attribs.begin(); it != m_Attribs.end(); ++it)
		it->second->Unbind();
    glUseProgram(0);
}


//------------------------------------------------------------------------------------------------
// LogShaderError
//
//------------------------------------------------------------------------------------------------
void Shader::LogShaderError(int handle, const std::string &info)
{
    char messages[256];
    glGetShaderInfoLog(handle, sizeof(messages), 0, &messages[0]);
    dry::Log(LogError, "[dryShader] Error compiling %s", info.c_str());
    dry::Log(LogError, messages);
}


//------------------------------------------------------------------------------------------------
// LogProgramError
//
//------------------------------------------------------------------------------------------------
void Shader::LogProgramError(int handle, const std::string &info)
{
    GLchar messages[256];
    glGetProgramInfoLog(handle, sizeof(messages), 0, &messages[0]);
    dry::Log(LogError, "[dryShader] Error compiling %s", info.c_str());
    dry::Log(LogError, messages);
}


//------------------------------------------------------------------------------------------------
// GetUniformByName
//
//------------------------------------------------------------------------------------------------
Uniform *Shader::GetUniformByName(const std::string &name)
{
	auto target = m_Uniforms.find(name);
	return (target == m_Uniforms.end()) ? NULL : target->second;
}


//------------------------------------------------------------------------------------------------
// GetAttribByName
//
//------------------------------------------------------------------------------------------------
Attrib *Shader::GetAttribByName(const std::string &name)
{
	auto target = m_Attribs.find(name);
	return (target == m_Attribs.end()) ? NULL : target->second;
}


//------------------------------------------------------------------------------------------------
// LoadUniforms
//
//------------------------------------------------------------------------------------------------
void Shader::LoadUniforms()
{
    GLint   count;
    GLint   len;
    GLint   size;
    GLenum  gltype;
    GLsizei length;
    char    name[1024];
    glGetProgramiv(m_Program, GL_ACTIVE_UNIFORMS, &count);
    glGetProgramiv(m_Program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &len);
    for (int i = 0; i < count; ++i)
    {
        glGetActiveUniform(m_Program, i, 1024, &length, &size, &gltype, name);
        m_Uniforms[name] = Uniform::Create(glGetUniformLocation(m_Program, name), gltype);
    }
}


//------------------------------------------------------------------------------------------------
// LoadAttribs
//
//------------------------------------------------------------------------------------------------
void Shader::LoadAttribs()
{
    GLint   count;
    GLint   len;
    GLint   size;
    GLenum  gltype;
    GLsizei length;
    char    name[1024];
    glGetProgramiv(m_Program, GL_ACTIVE_ATTRIBUTES, &count);
    glGetProgramiv(m_Program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &len);
    for (int i = 0; i < count; ++i)
    {
        glGetActiveAttrib(m_Program, i, 1024, &length, &size, &gltype, name);
        m_Attribs[name] = NEW Attrib(glGetAttribLocation(m_Program, name), gltype);
    }
}

