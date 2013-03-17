//
//  Time.mm
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"

static double s_TimeIni = [[NSDate date] timeIntervalSince1970];


//------------------------------------------------------------------------------------------------
// GetTime
//
//------------------------------------------------------------------------------------------------
float dry::GetTime()
{
    return (float)([[NSDate date] timeIntervalSince1970] - s_TimeIni);
}
