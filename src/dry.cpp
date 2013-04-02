//
//  dry.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"

using namespace dry;

#define MAX_STATIC_DIR 10

static std::string  s_PathBundle  = "";
static std::string  s_PathDocpath = "";
static LogLevel     s_LogLevel    = LogRelease;
static std::string  s_StaticDir[MAX_STATIC_DIR];
static int          s_StaticIdx = 0;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
void dry::Init(LogLevel loglevel, const std::string &logfile)
{
    s_LogLevel = loglevel;
    dry::Log(LogSystem, "dryGL v%s", DRY_VERSION_STR);
}


//------------------------------------------------------------------------------------------------
// Shut
//
//------------------------------------------------------------------------------------------------
void dry::Shut()
{
}


//------------------------------------------------------------------------------------------------
// Log
//
//------------------------------------------------------------------------------------------------
void dry::Log(LogLevel loglevel, const char *log, ...)
{
    if (s_LogLevel & loglevel)
    {
        char tmp[65535];
        va_list  body;
        va_start(body, log);
        vsprintf(tmp, log, body);
        va_end  (body);
        // Real print
        printf("%s\n", tmp);
    }
}


//------------------------------------------------------------------------------------------------
// SetPaths
//
//------------------------------------------------------------------------------------------------
void dry::SetPaths(const std::string &bundle, const std::string &docpath)
{
    s_PathBundle  = bundle;
    s_PathDocpath = docpath;
}


//------------------------------------------------------------------------------------------------
// GetFilePath
//
//------------------------------------------------------------------------------------------------
const std::string &dry::GetFilePath(const std::string &file)
{
    s_StaticIdx = (s_StaticIdx+1) % 10;
    s_StaticDir[s_StaticIdx] = s_PathBundle + "/" + file;
    return s_StaticDir[s_StaticIdx];
}


//------------------------------------------------------------------------------------------------
// GetFilePath
//
//------------------------------------------------------------------------------------------------
const std::string &dry::GetFilePath(const std::string &file, const std::string &docpath)
{
    s_StaticIdx = (s_StaticIdx+1) % 10;
    s_StaticDir[s_StaticIdx] = s_PathDocpath + "/" + file;
    return s_StaticDir[s_StaticIdx];
}
