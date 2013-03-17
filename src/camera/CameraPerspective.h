//
//  CameraPerspective.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

#include "Camera.h"

namespace dry {
    
class CameraPerspective : public Camera
{
public:
                CameraPerspective   ();

    void        Init                (float fov, float aspect, float near, float far);

protected:

    void        UpdateProjection    ();
    
protected:
    
    float       m_Fov;
    float       m_Aspect;
    float       m_Near;
    float       m_Far;
};

}