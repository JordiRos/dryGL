//
//  ImageLoader.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

class ImageLoader
{
public:
    static bool LoadImage       (Image       &img, string const &file);
    static bool LoadTexture     (Texture     &tex, string const &file, Texture::Params const &params);
    static bool LoadTextureCube (TextureCube &tex, string const &file, TextureCube::Params const &params);
};

}
