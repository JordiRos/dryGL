//
//  ImageUtils.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

namespace ImageUtils
{
    bool Load(Image       &img, string const &file);
    bool Load(Texture     &tex, string const &file, Texture::Params const &params);
    bool Load(TextureCube &tex, string const &file, TextureCube::Params const &params);
};

}
