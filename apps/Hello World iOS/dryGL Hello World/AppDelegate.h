//
//  AppDelegate.h
//  DryGL Hello World
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#import <UIKit/UIKit.h>
#include "HelloApp.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    HelloApp *app;
}

@property (strong, nonatomic) UIWindow *window;

@end
