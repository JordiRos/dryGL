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
    
// DRY platform target: TEMP only iOS for now
#define DRY_TARGET_IOS
#define DRY_VERSION_STR "0.1.0"
    
// PixelFormat
enum PixelFormat
{
    DRY_FMT_ALPHA,
    DRY_FMT_RGB565,
    DRY_FMT_RGB24,
    DRY_FMT_RGBA32,
};

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

void            Init        (const string &logfile);
void            Free        ();
void            Log         (const char *log, ...);
void            SetPaths    (const string &bundle, const string &docpath);  // Set directories
const string   &GetFilePath (const string &file);                           // Main bundle path
const string   &GetFilePath (const string &file, const string &docpath);    // Documents path
    
}

//------------------------------------------------------------------------------------------------
// Modules
//------------------------------------------------------------------------------------------------

// Glm
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// System
#include "system/App.h"
#include "system/Timer.h"
#include "system/Random.h"

// Graphics
#include "graphics/Color.h"
#include "graphics/Renderer.h"
#include "graphics/Texture.h"
#include "graphics/Shader.h"
#include "graphics/ShaderBasic.h"
#include "graphics/Pixels.h"
#include "graphics/Fbo.h"
#include "graphics/Vbo.h"

// Camera
#include "camera/Camera.h"
#include "camera/CameraPerspective.h"
#include "camera/CameraOrthogonal.h"

// Target iOS
#ifdef DRY_TARGET_IOS
    #include "ios/dry.h"
#endif
