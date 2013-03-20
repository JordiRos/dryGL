//
//  dry.h
//  dryGL main include
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

// Common includes
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// STL
#include <string>
using std::string;

// Null
#ifndef NULL
#define NULL 0
#endif

// Mem
#define NEW                         new
#define NEW_ARRAY(x,c)              new x[c]
#define DISPOSE(p)                  do { if (p) { delete   (p);  (p)  = NULL; } } while (0)
#define DISPOSE_ARRAY(p)            do { if (p) { delete [](p); (p) = NULL; } } while (0)
#define DISPOSE_ARRAY_P(p,n)        do { if (p) { for (int i=0; i<(int)n; i++) DISPOSE(p[i]); DISPOSE_ARRAY(p); } } while(0)
#define SAFE_RELEASE(p)             do { if (p) { (p)->Release(); (p)=NULL; } } while(0)

// Min/Max
#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

// Types
typedef unsigned char   uchar;
typedef unsigned short  ushort;
typedef unsigned int    uint;

//------------------------------------------------------------------------------------------------
// Dry
//------------------------------------------------------------------------------------------------
namespace dry {
    
#define DRY_TARGET_IOS                  // DRY platform target: only iOS for now
#define DRY_VERSION_STR     "0.1.0"     // DRY version
    
// AppParams
struct AppParams
{
    AppParams() {}
    AppParams(int width, int height, bool fullscreen)
    {
        Width      = width;
        Height     = height;
        Fullscreen = fullscreen;
    }
    int  Width;
    int  Height;
    bool Fullscreen;
};

// LogLevel
enum LogLevel
{
    LOG_SYSTEM  = 1<<0,
    LOG_WARNING = 1<<1,
    LOG_INFO    = 1<<2,
    LOG_DEBUG   = 1<<3,
    // Presets
    LOG_FLAG_WARNINGS = LOG_WARNING,
    LOG_FLAG_DEBUG = LOG_WARNING | LOG_INFO | LOG_DEBUG,
    LOG_FLAG_ALL = 0xFFFFFFFF,
};
    
void            Init        (LogLevel loglevel, const string &logfile);
void            Free        ();
void            Log         (LogLevel loglevel, const char *log, ...);
void            SetPaths    (const string &bundle, const string &docpath);  // Set app paths
const string   &GetFilePath (const string &file);                           // Main bundle path (read only)
const string   &GetFilePath (const string &file, const string &docpath);    // Documents path (read/write)
float           GetTime     ();                                             // Get system time

// PixelFormat
enum PixelFormat
{
    PF_ALPHA,
    PF_RGB565,
    PF_RGB24,
    PF_ARGB32,
    PF_UNKNOWN = 0xFFFFFFFF,
};

// BlendMode
enum BlendMode
{
    BLEND_ALPHA,
    BLEND_ADD,
    BLEND_PMALPHA,
    BLEND_PMADD,
    BLEND_SCREEN,
    BLEND_MULTIPLY,
    BLEND_UNKNOWN = 0xFFFFFFFF,
};

}

//------------------------------------------------------------------------------------------------
// Modules
//------------------------------------------------------------------------------------------------

// Glm
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// System
#include "system/Timer.h"
#include "system/Random.h"
#include "system/Color.h"
#include "system/App.h"

// Graphics
#include "graphics/Renderer.h"
#include "graphics/Image.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "graphics/ShaderBasic.h"
#include "graphics/Fbo.h"
#include "graphics/Vbo.h"
#include "graphics/Ibo.h"

// Camera
#include "camera/Camera.h"
#include "camera/CameraPerspective.h"
#include "camera/CameraOrthogonal.h"

// Scene
#include "scene/Material.h"
#include "scene/Geometry.h"
#include "scene/Mesh.h"

// Target iOS
#ifdef DRY_TARGET_IOS
    #include "ios/dry.h"
#endif
