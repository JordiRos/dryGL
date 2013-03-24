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
    
    void               *GetViewController   () { return m_ViewController; }

private:

    void               *m_ViewController;
};

}