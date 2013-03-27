//
//  Object.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

class Object
{
public:
                    Object          ();
    virtual        ~Object          () { Free(); }
    
    virtual bool    Init            ();
    virtual void    Free            ();

    virtual void    Update          ();
    virtual void    Draw            ();

    glm::vec3      &GetPosition     () { return m_Position; }
    glm::vec3      &GetScale        () { return m_Scale; }
    glm::vec3      &GetRotation     () { return m_Rotation; }
    glm::mat4      &GetTransform    () { return m_Transform; }
    
protected:

    glm::vec3       m_Position;
    glm::vec3       m_Scale;
    glm::vec3       m_Rotation;
    glm::mat4       m_Transform;
};
    
}
