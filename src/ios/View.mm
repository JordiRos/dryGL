//
//  View.mm
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "View.h"
#include "App.h"
#import <OpenGLES/EAGLDrawable.h>

@implementation dryView


//------------------------------------------------------------------------------------------------
// layerClass
//
//------------------------------------------------------------------------------------------------
+ (Class)layerClass
{
	return [CAEAGLLayer class];
}


//------------------------------------------------------------------------------------------------
// initWithFrame
//
//------------------------------------------------------------------------------------------------
- (id)initWithFrame:(CGRect)frame app:(dry::AppiOS *)app
{
    if (self = [super initWithFrame:frame])
    {
        self.multipleTouchEnabled = true;
        self.opaque = YES;
        m_App = app;

        // Layer
        m_EAGLLayer = (CAEAGLLayer *)super.layer;
        m_EAGLLayer.opaque = YES;
        m_EAGLLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:NO], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
        
        // Context
        m_EAGLContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        if (m_EAGLContext)
            [EAGLContext setCurrentContext:m_EAGLContext];
        else
            dry::Log(dry::LOG_WARNING, "[dryView] Failed to initialize OpenGLES 2.0 context");

        int w = app->GetParams().Width;
        int h = app->GetParams().Height;
        // Retina?
        m_ScaleFactor = 1;
        if ((w == 640  && h == 960)  || // iPhone4 Retina
            (w == 640  && h == 1136) || // iPhone5 Retina
            (w == 2048 && h == 1536))   // iPad3 Retina
        {
            m_ScaleFactor = 2;
        }
        self.contentScaleFactor = m_ScaleFactor;
        m_EAGLLayer.contentsScale = m_ScaleFactor;
        dry::Log(dry::LOG_SYSTEM, "[View] Initializing EAGLLayer view: %dx%d (scale %.2f)", w,h, m_ScaleFactor);

        // RenderBuffer
        glGenRenderbuffers(1, &m_ColorRenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_ColorRenderBuffer);
        [m_EAGLContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:m_EAGLLayer];

        // DepthBuffer/StencilBuffer
        glGenRenderbuffers(1, &m_DepthRenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, w,h);

        // FrameBuffer
        glGenFramebuffers(1, &m_FrameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_ColorRenderBuffer);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_RENDERBUFFER, m_DepthRenderBuffer);

        // Status Bar
        [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationFade];
    }
    return self;
}


//------------------------------------------------------------------------------------------------
// dealloc
//
//------------------------------------------------------------------------------------------------
- (void)dealloc
{
    [m_EAGLContext release];
	[super dealloc];
}


//------------------------------------------------------------------------------------------------
// beginRender
//
//------------------------------------------------------------------------------------------------
- (void)beginRender
{
    [EAGLContext setCurrentContext:m_EAGLContext];
    glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
}


//------------------------------------------------------------------------------------------------
// endRender
//
//------------------------------------------------------------------------------------------------
- (void)endRender
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_ColorRenderBuffer);
    [m_EAGLContext presentRenderbuffer:GL_RENDERBUFFER];
}


//------------------------------------------------------------------------------------------------
// onDraw
//
//------------------------------------------------------------------------------------------------
- (void)onDraw
{
    [self beginRender];
    if (m_App)
    {
        m_App->Update();
        m_App->Draw();
    }
    [self endRender];
}


//------------------------------------------------------------------------------------------------
// layoutSubviews
//
//------------------------------------------------------------------------------------------------
- (void)layoutSubviews
{
    dry::Log(dry::LOG_SYSTEM, "[View] layoutSubviews");
}


//------------------------------------------------------------------------------------------------
// startAnimation
//
//------------------------------------------------------------------------------------------------
- (void)startAnimation
{
	if (!m_Active)
    {
        m_DisplayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(onDraw)];
        [m_DisplayLink setFrameInterval:1];
        [m_DisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        m_Active = YES;
	}
}


//------------------------------------------------------------------------------------------------
// stopAnimation
//
//------------------------------------------------------------------------------------------------
- (void)stopAnimation
{
	if (m_Active)
    {
        [m_DisplayLink invalidate];
		m_DisplayLink = nil;
        m_Active = NO;
    }
}


@end
