//
//  Color.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_SYSTEM_COLOR_H_
#define DRY_SYSTEM_COLOR_H_

namespace dry {

// Byte Color
struct Color {
    Color() { Set(0); }
    Color(unsigned int color) { Set(color); }
    Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) { Set(_r,_g,_b,_a); }
    // Set
    void Set(unsigned int color)
    {
        *(unsigned int *)this = color;
    }
    void Set(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }
    unsigned int Get()
    {
        return *(unsigned int *)this;
    }
    // Data
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
};

}

#endif
