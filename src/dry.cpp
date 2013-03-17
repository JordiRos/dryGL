//
//  dry.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "freeimage/include/FreeImage.h"

// Private vars
static string s_pathBundle  = "";
static string s_pathDocpath = "";
static int    s_logLevel    = 0;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
void dry::Init(int loglevel, const string &logfile)
{
    s_logLevel = loglevel;
    dry::Log(LOG_SYSTEM, "dryGL v%s", DRY_VERSION_STR);
    dry::Log(LOG_SYSTEM, "[dry] Initializing FreeImage %s...", FreeImage_GetVersion());
    FreeImage_Initialise();
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void dry::Free()
{
}


//------------------------------------------------------------------------------------------------
// Log
//
//------------------------------------------------------------------------------------------------
void dry::Log(int loglevel, const char *log, ...)
{
    if (s_logLevel & loglevel)
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
void dry::SetPaths(const string &bundle, const string &docpath)
{
    s_pathBundle  = bundle;
    s_pathDocpath = docpath;
}


//------------------------------------------------------------------------------------------------
// GetPathFile
//
//------------------------------------------------------------------------------------------------
const string &dry::GetFilePath(const string &file)
{
    static string res;
    res = s_pathBundle + "/" + file;
    return res;
}


//------------------------------------------------------------------------------------------------
// GetPathFile
//
//------------------------------------------------------------------------------------------------
const string &dry::GetFilePath(const string &file, const string &docpath)
{
    static string res;
    res = s_pathDocpath + "/" + file;
    return res;
}
