//
//  Camera.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class Camera
{
public:
                        Camera          ();
    virtual            ~Camera          () { }

    virtual void        LookAt          (glm::vec3 const &position, glm::vec3 const &target, glm::vec3 const &up);
    virtual void        SetPosition     (glm::vec3 const &position);
    virtual void        SetTarget       (glm::vec3 const &target);
    virtual void        SetUp           (glm::vec3 const &up);

    glm::vec3 const    &GetPosition     () { return m_Position; }
    glm::vec3 const    &GetTarget       () { return m_Target; }
    glm::vec3 const    &GetUp           () { return m_Up; }
    glm::mat4 const    &GetMatView      () { return m_MatView; }

protected:
    
    void                Update          ();
    
protected:

    glm::vec3           m_Position;
    glm::vec3           m_Target;
    glm::vec3           m_Up;
    glm::mat4           m_MatView;
};

}