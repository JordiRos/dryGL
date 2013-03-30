//
//  ShaderLoader.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

class ShaderLoader
{
public:
    static bool Load(Shader &shader, string const &vs, string const &fs);
};

}
