//
//  HelloApp
//  DryGL Hello World
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "HelloApp.h"

dry::ShaderBasic _shader;
GLuint vbo_cube_vertices;
GLuint ibo_cube_elements;
GLuint uniform_mvp;

float _time = 0.f;

void render(int w,int h)
{
    // 1
    glViewport(0,0, w,h);
    
    _shader.Begin();

    // Load matrices
    float angle = _time * 45;  // 45° per second
    glm::vec3 axis_y(0, 1, 0);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_y);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -0.0));
    glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, -8.0), glm::vec3(0.0, 0.0, -0.0), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 projection = glm::perspective(45.0f, 1.0f*w/h, 0.1f, 10.0f);
    glm::mat4 mvp = projection * view * model * anim;
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
    glVertexAttribPointer(
                          0,                // attribute
                          3,                // number of elements per vertex, here (x,y,z)
                          GL_FLOAT,         // the type of each element
                          GL_FALSE,         // take our values as-is
                          0,                // no extra data between each position
                          0                 // offset of first element
                          );
    /* Push each element in buffer_vertices to the vertex shader */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    glDisableVertexAttribArray(0);
    
    _shader.End();
}

void HelloApp::Init()
{
    // Vertices
    GLfloat cube_vertices[] = {
        // front
        -1.0, -1.0,  1.0,
        1.0, -1.0,  1.0,
        1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
        // back
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0,
    };
    glGenBuffers(1, &vbo_cube_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
    
    // Indices
    GLushort cube_elements[] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // top
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // bottom
        4, 0, 3,
        3, 7, 4,
        // left
        4, 5, 1,
        1, 0, 4,
        // right
        3, 2, 6,
        6, 7, 3,
    };
    glGenBuffers(1, &ibo_cube_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    // Shader
    _shader.Init();
    int programHandle = _shader.GetShader()->GetHandleProgram();
    
    uniform_mvp = glGetUniformLocation(programHandle, "ModelViewProjection");
    
    /*
    glBindAttribLocation(programHandle, 0, "aPos");
    
    _positionSlot = glGetAttribLocation(programHandle, "aPos");
    _colorSlot = glGetAttribLocation(programHandle, "aColor");
    glEnableVertexAttribArray(_positionSlot);
    glEnableVertexAttribArray(_colorSlot);
    
    _projectionUniform = glGetUniformLocation(programHandle, "projection");
    _modelViewUniform = glGetUniformLocation(programHandle, "modelview");
    
    _texCoordSlot = glGetAttribLocation(programHandle, "aTexCoord");
    glEnableVertexAttribArray(_texCoordSlot);
    _textureUniform = glGetUniformLocation(programHandle, "texture");
    */
}


void HelloApp::Update()
{
}

void HelloApp::Draw()
{
    _time += 1.f/60.f;
    float r = fmod(_time, 1.f);
    glClearColor(0, r, 55.0/255.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    render(GetParams().Width, GetParams().Height);
}
