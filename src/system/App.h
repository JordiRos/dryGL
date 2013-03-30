//
//  App.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class Renderer;

class App
{
public:

                        App                 (AppParams const &params);
    virtual            ~App                 ();

    // Events
    virtual void        OnInit              () {}
    virtual void        OnUpdate            () {}
	virtual void        OnDraw              () {}

	virtual void        OnTouchDown         (float x, float y, int id) {}
	virtual void        OnTouchMoved        (float x, float y, int id) {}
	virtual void        OnTouchUp           (float x, float y, int id) {}
	virtual void        OnTouchDoubleTap    (float x, float y, int id) {}
	virtual void        OnTouchCancelled    (float x, float y, int id) {}

    virtual void        OnRotate            (DeviceOrientation orientation) {}
	virtual void        OnLostFocus         () {}
	virtual void        OnGotFocus          () {}
	virtual void        OnMemoryWarning     () {}

    // App
    void                SetRenderer         (Renderer *renderer) { m_Renderer = renderer; }

    AppParams const    &GetParams           () { return m_Params; }
    Renderer           *GetRenderer         () { return m_Renderer; }
    Timer              &GetTimer            () { return m_Timer; }
    float               GetTime             () { return m_Time; }
    float               GetDelta            () { return m_Delta; }
    
    void                Update              ();
    void                Draw                ();

protected:
 
    AppParams           m_Params;
    Renderer           *m_Renderer;
    Timer               m_Timer;
    float               m_Time;
    float               m_Delta;
};

}
