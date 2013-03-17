//
//  CameraOrthogonal.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

#include "Camera.h"

namespace dry {
    
class CameraOrthogonal : public Camera
{
public:
                CameraOrthogonal    ();

    void        Init                (float left, float right, float top, float bottom, float near, float far);

protected:

    void        UpdateProjection    ();
    
protected:
    
    float       m_Left;
    float       m_Right;
    float       m_Top;
    float       m_Bottom;
    float       m_Near;
    float       m_Far;
};

}