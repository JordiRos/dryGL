//
//  ImageUtils.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_IOS_IMAGEUTILS_H_
#define DRY_IOS_IMAGEUTILS_H_

namespace dry {

namespace ImageUtils
{
    bool Load(Image       &img, const std::string &file);
    bool Load(Texture     &tex, const std::string &file, Texture::Params const &params);
    bool Load(TextureCube &tex, const std::string &file, TextureCube::Params const &params);
};

}

#endif
