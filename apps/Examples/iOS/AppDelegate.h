//
//  AppDelegate.h
//  DryGL Hello World
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    dry::AppiOS *app;
}

@property (strong, nonatomic) UIWindow *window;

@end
