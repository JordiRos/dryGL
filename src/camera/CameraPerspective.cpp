//
//  CameraPerspective.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "CameraPerspective.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// CameraPerspective
//
//------------------------------------------------------------------------------------------------
CameraPerspective::CameraPerspective() : Camera()
{
    m_Fov    = 45.f;
    m_Aspect = 1.f;
    m_Near   = 1.f;
    m_Far    = 1000.f;
}


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
void CameraPerspective::Init(float fov, float aspect, float near, float far)
{
    m_Fov    = fov;
    m_Aspect = aspect;
    m_Near   = near;
    m_Far    = far;
    UpdateProjection();
}


//------------------------------------------------------------------------------------------------
// UpdateProjection
//
//------------------------------------------------------------------------------------------------
void CameraPerspective::UpdateProjection()
{
    m_MatProjection = glm::perspective(m_Fov, m_Aspect, m_Near, m_Far);
}
