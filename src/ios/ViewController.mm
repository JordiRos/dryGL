//
//  ViewController.mm
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "ViewController.h"
#include "View.h"

@implementation dryViewController

@synthesize glView;


//------------------------------------------------------------------------------------------------
// initWithFrame
//
//------------------------------------------------------------------------------------------------
- (id)initWithFrame:(CGRect)frame app:(dry::AppiOS *)app
{
    dry::Log("[ViewController] initWithFrame");
    if ((self = [super init]))
    {
        glView = [[[dryView alloc] initWithFrame:frame app:app] autorelease];
        [self.view addSubview:glView];
    }
    return self;
}


//------------------------------------------------------------------------------------------------
// dealloc
//
//------------------------------------------------------------------------------------------------
- (void) dealloc
{
    dry::Log("[ViewController] dealloc");
    [glView stopAnimation];
    [glView removeFromSuperview];
    glView = nil;
    [super dealloc];
}


//------------------------------------------------------------------------------------------------
// viewDidLoad
//
//------------------------------------------------------------------------------------------------
- (void)viewDidLoad
{
    dry::Log("[ViewController] viewDidLoad");
    [super viewDidLoad];
    [glView startAnimation];
}


//------------------------------------------------------------------------------------------------
// viewWillAppear
//
//------------------------------------------------------------------------------------------------
- (void)viewWillAppear:(BOOL)animated
{
    dry::Log("[ViewController] viewWillAppear");
    [super viewWillAppear:animated];
    [glView startAnimation];
}


//------------------------------------------------------------------------------------------------
// viewDidDisappear
//
//------------------------------------------------------------------------------------------------
- (void)viewDidDisappear:(BOOL)animated
{
    dry::Log("[ViewController] viewDidDisappear");
    [super viewDidDisappear:animated];
    [glView stopAnimation];
}


@end
