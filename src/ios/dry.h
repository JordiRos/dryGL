//
//  dry.h
//  dryGL iOS header
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_IOS_DRY_H_
#define DRY_IOS_DRY_H_

// Headers
#ifdef __OBJC__
    #import <UIKit/UIKit.h>
    #import <Foundation/Foundation.h>
    #import <QuartzCore/QuartzCore.h>
    // EAGL
    #import <OpenGLES/EAGL.h>
    #import <OpenGLES/EAGLDrawable.h>
    // iOS
    #import "View.h"
    #import "ViewController.h"
#endif

// ES2
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

// dry
#include "ImageUtils.h"
#include "ShaderUtils.h"

#endif
