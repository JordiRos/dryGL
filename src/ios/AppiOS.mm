//
//  AppiOS.mm
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "AppiOS.h"
#include "ViewController.h"


//------------------------------------------------------------------------------------------------
// Format
//
//------------------------------------------------------------------------------------------------
static string Format(NSString const *nsstr)
{
    return string([nsstr UTF8String]);
}


//------------------------------------------------------------------------------------------------
// Constructor
//
//------------------------------------------------------------------------------------------------
dry::AppiOS::AppiOS(AppParams const &params) : App(params)
{
    m_ViewController = [[[dryViewController alloc] initWithFrame:[[UIScreen mainScreen] bounds] app:this] autorelease];
    string pathBundle  = Format([[NSBundle mainBundle] bundlePath]);
    string pathDocpath = Format(NSHomeDirectory());
    dry::SetPaths(pathBundle, pathDocpath);
}
