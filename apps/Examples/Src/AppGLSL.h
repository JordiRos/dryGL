//
//  AppGLSL.h
//  dryExamples
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#import "dry.h"

class AppGLSL : public dry::AppiOS
{
public:
            AppGLSL (dry::AppParams const &params);
    void    Update  (float time, float delta);
    void    Draw    ();
};
