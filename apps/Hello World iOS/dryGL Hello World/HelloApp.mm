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

float _time = 0.f;

void render()
{
    // 1
    glViewport(0,0, 640,960);
    
    _shader.Begin();

    static GLfloat vVertices[] = {0.0f, 0.5f, 0.0f,
                            -0.5f, -0.5f, 0.0f,
                            0.5f, -0.5f, 0.0f};
    // Load the vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    _shader.End();
}

void HelloApp::Init()
{
    _shader.Init();
    int programHandle = _shader.GetShader()->GetHandleProgram();

    glBindAttribLocation(programHandle, 0, "aPos");
    
    /*
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
    render();
}
