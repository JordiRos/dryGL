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

    virtual void        LookAt          (glm::vec3 const &position, glm::vec3 const &target, glm::vec3 const &up);
    virtual void        SetPosition     (glm::vec3 const &position);
    virtual void        SetTarget       (glm::vec3 const &target);
    virtual void        SetUp           (glm::vec3 const &up);

    glm::vec3 const    &GetPosition     () const { return m_Position; }
    glm::vec3 const    &GetTarget       () const { return m_Target; }
    glm::vec3 const    &GetUp           () const { return m_Up; }
    glm::mat4 const    &GetMatView      () const { return m_MatView; }
    glm::mat4 const    &GetMatProj      () const { return m_MatProj; }

protected:
    
    void                Update          ();
    
protected:

    glm::vec3           m_Position;
    glm::vec3           m_Target;
    glm::vec3           m_Up;
    glm::mat4           m_MatView;
    glm::mat4           m_MatProj;
};

}