//
//  AppSimple.h
//  dryExamples
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#import "dry.h"

class AppSimple : public dry::AppiOS
{
public:
            AppSimple   (dry::AppParams const &params);
    void    Update      ();
    void    Draw        ();
};
