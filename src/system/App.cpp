//
//  App.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "App.h"
#include "Renderer.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Constructor
//
//------------------------------------------------------------------------------------------------
App::App(AppParams const &params)
{
    m_Params = params;
}


//------------------------------------------------------------------------------------------------
// Destructor
//
//------------------------------------------------------------------------------------------------
App::~App()
{
    DISPOSE(m_Renderer);
}
