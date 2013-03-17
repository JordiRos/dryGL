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

                        App             (AppParams const &params) { m_Params = params; }
    virtual            ~App             () { Free(); }

    virtual void        Init            ();
    virtual void        Free            ();
	virtual void        Update          () {}
	virtual void        Draw            () {}

	virtual void        TouchDown       (int x, int y, int id) {}
	virtual void        TouchMoved      (int x, int y, int id) {}
	virtual void        TouchUp         (int x, int y, int id) {}
	virtual void        TouchDoubleTap  (int x, int y, int id) {}
	virtual void        TouchCancelled  (int x, int y, int id) {}

	virtual void        LostFocus       () {}
	virtual void        GotFocus        () {}
	virtual void        MemoryWarning   () {}

    AppParams const    &GetParams       () { return m_Params; }
    Timer              &GetTimer        () { return m_Timer; }
    Renderer           *GetRenderer     () { return m_Renderer; }

protected:
 
    AppParams           m_Params;
    Timer               m_Timer;
    Renderer           *m_Renderer;
};

}