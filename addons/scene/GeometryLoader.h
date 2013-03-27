//
//  GeometryLoader.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

class Geometry;
    
class GeometryLoader
{
public:
    static bool LoadGeometry(Geometry &geo, string const &file);
};
    
}
