//
//  HelloApp.h
//  DryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#import "dry.h"

class HelloApp : public dry::AppiOS
{
public:
            HelloApp(dry::AppParams const &params) : dry::AppiOS(params) {}
    void    Init    ();
    void    Update  ();
    void    Draw    ();
};
