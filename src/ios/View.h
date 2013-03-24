//
//  View.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once


@interface dryView : UIView
{
    CAEAGLLayer    *m_EAGLLayer;
    EAGLContext    *m_EAGLContext;
    bool            m_Active;
	id              m_DisplayLink;
    float           m_ScaleFactor;
    float           m_Time;
    bool            m_First;
    dry::AppiOS    *m_App;
    dry::Renderer  *m_Renderer;
}

- (id)initWithFrame:(CGRect)frame app:(dry::AppiOS *)app;
- (void)startAnimation;
- (void)stopAnimation;

@end
