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
    m_Left   =-1.f;
    m_Top    =-1.f;
    m_Right  = 1.f;
    m_Bottom = 1.f;
    m_Near   = 1.f;
    m_Far    = 1000.f;
}


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
void CameraOrthogonal::Init(float left, float top, float right, float bottom, float near, float far)
{
    m_Left   = left;
    m_Top    = top;
    m_Right  = right;
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
    // It's really left,right,bottom,top, but that inverts Y in OpenGL, so we flip Bottom / Top
    m_MatProj = glm::ortho(m_Left, m_Right, m_Top, m_Bottom, m_Near, m_Far);
}
