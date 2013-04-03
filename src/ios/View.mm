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
- (id)initWithFrame:(CGRect)frame app:(dry::App *)app
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
            dry::Log(dry::LogError, "[dryView] Failed to initialize OpenGLES 2.0 context");

        int w = app->GetParams().Width;
        int h = app->GetParams().Height;
        // Retina?
        m_ScaleFactor = app->GetParams().Retina ? 2 : 1;
        self.contentScaleFactor = m_ScaleFactor;
        m_EAGLLayer.contentsScale = m_ScaleFactor;
        dry::Log(dry::LogSystem, "[View] Initializing GLView: %dx%d (scale %.2f)", w,h, m_ScaleFactor);

        // Renderer
        m_Renderer = NEW dry::Renderer(w, h, true, true);
        app->SetRenderer(m_Renderer);
        app->OnInit();

        // Bind render buffer to EAGLLayer
        glBindRenderbuffer(GL_RENDERBUFFER, m_Renderer->GetColorBuffer());
        [m_EAGLContext renderbufferStorage:GL_RENDERBUFFER fromDrawable:m_EAGLLayer];

        // Status Bar
        [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationFade];

        // Rotation
        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onRotate:) name:UIDeviceOrientationDidChangeNotification object:nil];
    }
    return self;
}


//------------------------------------------------------------------------------------------------
// dealloc
//
//------------------------------------------------------------------------------------------------
- (void)dealloc
{
    DISPOSE(m_Renderer);
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
    m_Renderer->Begin();
}


//------------------------------------------------------------------------------------------------
// endRender
//
//------------------------------------------------------------------------------------------------
- (void)endRender
{
    m_Renderer->End();
    [m_EAGLContext presentRenderbuffer:GL_RENDERBUFFER];
}


//------------------------------------------------------------------------------------------------
// onDraw
//
//------------------------------------------------------------------------------------------------
- (void)onDraw
{
    if (!m_Renderer->GetRendering())
    {
        [self beginRender];
        if (m_App)
        {
            m_App->Update();
            m_App->Draw  ();
        }
        [self endRender];
    }
    else
        dry::Log(dry::LogWarning, "[View] onDraw called when Renderer already in render loop");
}


//------------------------------------------------------------------------------------------------
// layoutSubviews
//
//------------------------------------------------------------------------------------------------
- (void)layoutSubviews
{
    dry::Log(dry::LogInfo, "[View] layoutSubviews");
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
        if (m_App)
            m_App->GetTimer().Resume();
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
        if (m_App)
            m_App->GetTimer().Pause();
    }
}


//------------------------------------------------------------------------------------------------
// onRotate
//
//------------------------------------------------------------------------------------------------
- (void)onRotate:(NSNotification *)notification
{
    UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
    dry::Log(dry::LogInfo, "[View] didRotate: %d", orientation);
}


//------------------------------------------------------------------------------------------------
// touchesBegan
//
//------------------------------------------------------------------------------------------------
-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (m_App)
    {
        UITouch *touch    = [touches anyObject];
        CGPoint  location = [touch locationInView:self];
        float x = location.x * m_ScaleFactor;
        float y = location.y * m_ScaleFactor;
        dry::Log(dry::LogInfo, "[View] touchesBegan: %.2f,%.2f", x, y);
        m_App->OnTouchDown(x, y, 0);
    }
}


//------------------------------------------------------------------------------------------------
// touchesMoved
//
//------------------------------------------------------------------------------------------------
-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (m_App)
    {
        UITouch *touch    = [touches anyObject];
        CGPoint  location = [touch locationInView:self];
        float x = location.x * m_ScaleFactor;
        float y = location.y * m_ScaleFactor;
        dry::Log(dry::LogInfo, "[View] touchesMoved: %.2f,%.2f", x, y);
        m_App->OnTouchMoved(x, y, 0);
    }
}


//------------------------------------------------------------------------------------------------
// touchesEnded
//
//------------------------------------------------------------------------------------------------
-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    if (m_App)
    {
        UITouch *touch    = [touches anyObject];
        CGPoint  location = [touch locationInView:self];
        float x = location.x * m_ScaleFactor;
        float y = location.y * m_ScaleFactor;
        dry::Log(dry::LogInfo, "[View] touchesEnded: %.2f,%.2f", x, y);
        m_App->OnTouchUp(x, y, 0);
    }
}


//------------------------------------------------------------------------------------------------
// touchesCancelled
//
//------------------------------------------------------------------------------------------------
-(void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self touchesEnded:touches withEvent:event];
}


@end
