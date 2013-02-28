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
    GLuint          m_ColorRenderBuffer;
    GLuint          m_DepthRenderBuffer;
    GLuint          m_FrameBuffer;
    BOOL            m_Active;
	id              m_DisplayLink;
    dry::AppiOS    *m_App;
}

- (id)initWithFrame:(CGRect)frame app:(dry::AppiOS *)app;
- (void)startAnimation;
- (void)stopAnimation;

@end
