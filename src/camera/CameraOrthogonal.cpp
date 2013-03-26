//
//  CameraOrthogonal.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "CameraOrthogonal.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// CameraOrthogonal
//
//------------------------------------------------------------------------------------------------
CameraOrthogonal::CameraOrthogonal() : Camera()
{
    m_Left   = 0.f;
    m_Right  = 1.f;
    m_Top    = 0.f;
    m_Bottom = 1.f;
    m_Near   = 1.f;
    m_Far    = 1000.f;
}


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
void CameraOrthogonal::Init(float left, float right, float top, float bottom, float near, float far)
{
    m_Left   = left;
    m_Right  = right;
    m_Top    = top;
    m_Bottom = bottom;
    m_Near   = near;
    m_Far    = far;
    UpdateProjection();
}


//------------------------------------------------------------------------------------------------
// UpdateProjection
//
//------------------------------------------------------------------------------------------------
void CameraOrthogonal::UpdateProjection()
{
    m_MatProj = glm::ortho(m_Left, m_Right, m_Top, m_Bottom, m_Near, m_Far);
}
