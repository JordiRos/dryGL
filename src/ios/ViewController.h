//
//  ViewController.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_IOS_VIEWCONTROLLER_H_
#define DRY_IOS_VIEWCONTROLLER_H_

#import "View.h"

class dry::App;

@interface dryViewController : UIViewController <UIApplicationDelegate>
{
    dryView *glView;
}

@property (readonly, nonatomic) dryView *glView;

- (id)initWithFrame:(CGRect)frame app:(dry::App *)app;

@end

#endif