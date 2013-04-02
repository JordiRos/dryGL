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
static std::string Format(const NSString *nsstr)
{
    return std::string([nsstr UTF8String]);
}


//------------------------------------------------------------------------------------------------
// Constructor
//
//------------------------------------------------------------------------------------------------
dry::AppiOS::AppiOS(AppParams const &params) : App(params)
{
    m_ViewController = [[[dryViewController alloc] initWithFrame:[[UIScreen mainScreen] bounds] app:this] autorelease];
    std::string pathBundle  = Format([[NSBundle mainBundle] bundlePath]);
    std::string pathDocpath = Format(NSHomeDirectory());
    dry::SetPaths(pathBundle, pathDocpath);
}
