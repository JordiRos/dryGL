//
//  AppiOS.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class AppiOS : public App
{
public:
                        AppiOS              (AppParams const &params);
    virtual            ~AppiOS              () { Free(); }

    virtual void        Init                ();
    virtual void        Free                ();
	virtual void        Update              () {}
	virtual void        Draw                () {}
    
	virtual void        TouchDown           (int x, int y, int id) {}
	virtual void        TouchMoved          (int x, int y, int id) {}
	virtual void        TouchUp             (int x, int y, int id) {}
	virtual void        TouchDoubleTap      (int x, int y, int id) {}
	virtual void        TouchCancelled      (int x, int y, int id) {}
    
	virtual void        LostFocus           () {}
	virtual void        GotFocus            () {}
	virtual void        MemoryWarning       () {}
    
    void               *GetViewController   () { return m_ViewController; }

private:

    void               *m_ViewController;
};

}