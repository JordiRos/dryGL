//
//  Object.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Object.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Update
//
//------------------------------------------------------------------------------------------------
void Object::Update()
{
    m_Transform = glm::translate(m_Position) * glm::scale(m_Scale) * glm::rotate(1.f, m_Rotation.x, m_Rotation.y, m_Rotation.z);
}
