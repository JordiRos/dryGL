//
//  Time.mm
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"

static double s_TimeIni = -1;


//------------------------------------------------------------------------------------------------
// GetTime
//
//------------------------------------------------------------------------------------------------
float dry::GetTime()
{
    if (s_TimeIni < 0)
        s_TimeIni = [[NSDate date] timeIntervalSince1970];
    return (float)([[NSDate date] timeIntervalSince1970] - s_TimeIni);
}
