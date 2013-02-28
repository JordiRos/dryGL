//
//  ViewController.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

#import "View.h"

class dry::AppiOS;

@interface dryViewController : UIViewController <UIApplicationDelegate>
{
    dryView *glView;
}

@property (readonly, nonatomic) dryView *glView;

- (id)initWithFrame:(CGRect)frame app:(dry::AppiOS *)app;

@end
