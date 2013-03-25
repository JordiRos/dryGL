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

                        App             (AppParams const &params);
    virtual            ~App             ();

    virtual void        Init            () {}
	virtual void        Update          (float time, float delta) {}
	virtual void        Draw            () {}

	virtual void        TouchDown       (float x, float y, int id) {}
	virtual void        TouchMoved      (float x, float y, int id) {}
	virtual void        TouchUp         (float x, float y, int id) {}
	virtual void        TouchDoubleTap  (float x, float y, int id) {}
	virtual void        TouchCancelled  (float x, float y, int id) {}

    virtual void        OnRotate        (DeviceOrientation orientation) {}
	virtual void        LostFocus       () {}
	virtual void        GotFocus        () {}
	virtual void        MemoryWarning   () {}

    void                SetRenderer     (Renderer *renderer) { m_Renderer = renderer; }

    AppParams const    &GetParams       () { return m_Params; }
    Timer              &GetTimer        () { return m_Timer; }
    Renderer           *GetRenderer     () { return m_Renderer; }

protected:
 
    AppParams           m_Params;
    Timer               m_Timer;
    Renderer           *m_Renderer;
};

}