//
//  ShaderUtils.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_IOS_SHADERUTILS_H_
#define DRY_IOS_SHADERUTILS_H_

namespace dry {

namespace ShaderUtils
{
    bool Load(Shader &shader, const std::string &vs, const std::string &fs);
};

}

#endif
