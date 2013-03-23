//
//  AppDelegate.m
//  DryGL Hello World
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#import "AppDelegate.h"
#import "AppVbo.h"
#import "AppFbo.h"
#import "AppGLSL.h"
#import "AppGeometry.h"


@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    CGRect frame = [[UIScreen mainScreen] bounds];
    self.window = [[[UIWindow alloc] initWithFrame:frame] autorelease];

    // Initialize dry subsystem
    dry::Init(dry::LOG_FLAG_ALL, "dry.log");
    dry::Log(dry::LOG_INFO, "[AppDelegate] Screen Size: %.0f,%.0f", frame.size.width,frame.size.height);
    
    // Create app with desired resolution and attach its viewController to rootViewController
    //app = NEW AppVbo(dry::AppParams(frame.size.width,frame.size.height, false));
    //app = NEW AppFbo(dry::AppParams(frame.size.width,frame.size.height, false));
    //app = NEW AppGLSL(dry::AppParams(frame.size.width,frame.size.height, false));
    app = NEW AppGeometry(dry::AppParams(frame.size.width,frame.size.height, false));
    self.window.rootViewController = (UIViewController *)app->GetViewController();

    [self.window makeKeyAndVisible];
    
    return YES;
}

- (void)dealloc
{
    DISPOSE(app);
    [super dealloc];
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end