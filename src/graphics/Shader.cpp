//
//  Shader.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Shader.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// InitWithProgram
//
//------------------------------------------------------------------------------------------------
bool Shader::InitWithProgram(const char *vs, const char *fs)
{
    Free();
    bool res = true;
    
    int lenVS = strlen(vs);
    int lenFS = strlen(fs);
    int result;
    
    // Create VS
    m_HandleVS = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource (m_HandleVS, 1, (GLchar const **)&vs, &lenVS);
    glCompileShader(m_HandleVS);
    glGetShaderiv  (m_HandleVS, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        LogShaderError(m_HandleVS, "vertex shader");
        res = false;
    }

    // Create FS
    m_HandleFS = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource (m_HandleFS, 1, (GLchar const **)&fs, &lenFS);
    glCompileShader(m_HandleFS);
    glGetShaderiv  (m_HandleFS, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        LogShaderError(m_HandleFS, "fragment shader");
        res = false;
    }
    
    // Create Program
    if (res)
    {
        m_HandleProgram = glCreateProgram();
        glAttachShader(m_HandleProgram, m_HandleVS);
        glAttachShader(m_HandleProgram, m_HandleFS);
        glLinkProgram (m_HandleProgram);
        glGetProgramiv(m_HandleProgram, GL_LINK_STATUS, &result);
        if (result == GL_FALSE)
        {
            LogProgramError(m_HandleProgram, "program");
            res = false;
        }
    }
    
    // Clean?
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
    if (m_HandleProgram != -1) glDeleteProgram(m_HandleProgram);
    if (m_HandleVS != -1) glDeleteShader(m_HandleVS);
    if (m_HandleFS != -1) glDeleteShader(m_HandleFS);
    m_HandleProgram = -1;
    m_HandleVS = -1;
    m_HandleFS = -1;
}


//------------------------------------------------------------------------------------------------
// Bind
//
//------------------------------------------------------------------------------------------------
void Shader::Bind()
{
    glUseProgram(m_HandleProgram);
}


//------------------------------------------------------------------------------------------------
// Unbind
//
//------------------------------------------------------------------------------------------------
void Shader::Unbind()
{
    glUseProgram(0);
}


//------------------------------------------------------------------------------------------------
// LogShaderError
//
//------------------------------------------------------------------------------------------------
void Shader::LogShaderError(int handle, const string &info)
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
void Shader::LogProgramError(int handle, const string &info)
{
    GLchar messages[256];
    glGetProgramInfoLog(handle, sizeof(messages), 0, &messages[0]);
    dry::Log(LogError, "[dryShader] Error compiling %s", info.c_str());
    dry::Log(LogError, messages);
}


//------------------------------------------------------------------------------------------------
// GetAttribLocation
//
//------------------------------------------------------------------------------------------------
int Shader::GetAttribLocation(const char *name)
{
    int attribute = glGetAttribLocation(m_HandleProgram, name);
    if (attribute < 0)
        dry::Log(LogWarning, "[Shader] Can't find attribute %s", name);
    return attribute;
}


//------------------------------------------------------------------------------------------------
// GetUniformLocation
//
//------------------------------------------------------------------------------------------------
int Shader::GetUniformLocation(const char *name)
{
    int uniform = glGetUniformLocation(m_HandleProgram, name);
    if (uniform < 0)
        dry::Log(LogWarning, "[Shader] Can't find uniform %s", name);
    return uniform;
}
