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
static string pathBundle  = "";
static string pathDocpath = "";


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
void dry::Init(const string &logfile)
{
    dry::Log("dryGL v%s", DRY_VERSION_STR);
    dry::Log("[dry] Initializing FreeImage %s...", FreeImage_GetVersion());
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
void dry::Log(const char *log, ...)
{
    char tmp[65535];
    va_list  body;
    va_start(body, log);
    vsprintf(tmp, log, body);
    va_end  (body);
    // Real print
    printf("%s\n", tmp);
}


//------------------------------------------------------------------------------------------------
// SetPaths
//
//------------------------------------------------------------------------------------------------
void dry::SetPaths(const string &bundle, const string &docpath)
{
    pathBundle  = bundle;
    pathDocpath = docpath;
}


//------------------------------------------------------------------------------------------------
// GetPathFile
//
//------------------------------------------------------------------------------------------------
const string &dry::GetFilePath(const string &file)
{
    static string res;
    res = pathBundle + "/" + file;
    return res;
}


//------------------------------------------------------------------------------------------------
// GetPathFile
//
//------------------------------------------------------------------------------------------------
const string &dry::GetFilePath(const string &file, const string &docpath)
{
    static string res;
    res = pathDocpath + "/" + file;
    return res;
}
