//
//  MeshMaterialDiffuse.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

#include "../MeshMaterial.h"

namespace dry {

class MeshMaterialDiffuse : public MeshMaterial
{
public:
                    MeshMaterialDiffuse () { }
                   ~MeshMaterialDiffuse () { Free(); }
    
    virtual bool    Init                ();
    virtual void    Free                ();
};
    
}
