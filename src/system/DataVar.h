//
//  DataVar.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

// DataVar variant with unions
union DataVar
{
    DataVar() { };
    int         i;
    float       f;
    glm::vec2   v2;
    glm::vec3   v3;
    glm::vec4   v4;
    glm::mat2   m2;
    glm::mat3   m3;
    glm::mat4   m4;
    int         &operator=(int       value) { i  = value; return i; }
    float       &operator=(float     value) { f  = value; return f; }
    glm::vec2   &operator=(glm::vec2 value) { v2 = value; return v2; }
    glm::vec3   &operator=(glm::vec3 value) { v3 = value; return v3; }
    glm::vec4   &operator=(glm::vec4 value) { v4 = value; return v4; }
    glm::mat2   &operator=(glm::mat2 value) { m2 = value; return m2; }
    glm::mat3   &operator=(glm::mat3 value) { m3 = value; return m3; }
    glm::mat4   &operator=(glm::mat4 value) { m4 = value; return m4; }
};

}
