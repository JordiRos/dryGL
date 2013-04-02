//
//  Camera.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_CAMERA_CAMERA_H_
#define DRY_CAMERA_CAMERA_H_

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
    glm::mat4 const    &GetView         () const { return m_View; }
    glm::mat4 const    &GetProjection   () const { return m_Projection; }

protected:
    
    virtual void        Update          ();
    
protected:

    glm::vec3           m_Position;
    glm::vec3           m_Target;
    glm::vec3           m_Up;
    glm::mat4           m_View;
    glm::mat4           m_Projection;
};

}

#endif