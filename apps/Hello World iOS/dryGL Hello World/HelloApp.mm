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
dry::Pixels _pixels;
dry::Texture _texture;
dry::CameraPerspective _camera;
//dry::CameraOrthogonal _camera;
GLuint attr_position;
GLuint attr_texcoord;
GLuint vbo_cube_vertices;
GLuint vbo_cube_texcoords;
GLuint ibo_cube_elements;
GLuint uniform_mvp;
GLuint uniform_texture;

float _time = 0.f;

void HelloApp::Init()
{
    // Vertices
    GLfloat cube_vertices[] = {
        // front
        -1.0, -1.0,  1.0,
        1.0, -1.0,  1.0,
        1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
        // top
        -1.0,  1.0,  1.0,
        1.0,  1.0,  1.0,
        1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0,
        // back
        1.0, -1.0, -1.0,
        -1.0, -1.0, -1.0,
        -1.0,  1.0, -1.0,
        1.0,  1.0, -1.0,
        // bottom
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0, -1.0,  1.0,
        -1.0, -1.0,  1.0,
        // left
        -1.0, -1.0, -1.0,
        -1.0, -1.0,  1.0,
        -1.0,  1.0,  1.0,
        -1.0,  1.0, -1.0,
        // right
        1.0, -1.0,  1.0,
        1.0, -1.0, -1.0,
        1.0,  1.0, -1.0,
        1.0,  1.0,  1.0,
    };
    glGenBuffers(1, &vbo_cube_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    // TexCoords
    GLfloat cube_texcoords[2*4*6] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
    };
    for (int i = 1; i < 6; i++)
        memcpy(&cube_texcoords[i*4*2], &cube_texcoords[0], 2*4*sizeof(GLfloat));
    glGenBuffers(1, &vbo_cube_texcoords);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texcoords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_texcoords), cube_texcoords, GL_STATIC_DRAW);
    
    // Indices
    GLushort cube_elements[] = {
        // front
        0,  1,  2,
        2,  3,  0,
        // top
        4,  5,  6,
        6,  7,  4,
        // back
        8,  9, 10,
        10, 11,  8,
        // bottom
        12, 13, 14,
        14, 15, 12,
        // left
        16, 17, 18,
        18, 19, 16,
        // right
        20, 21, 22,
        22, 23, 20,
    };
    glGenBuffers(1, &ibo_cube_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
    
    // Texture
    _pixels.InitWithFile(dry::GetFilePath("texture.png"));
    _texture.InitWithPixels(_pixels);
    
    // Shader
    _shader.Init();
    int programHandle = _shader.GetShader()->GetHandleProgram();
    attr_position = glGetAttribLocation(programHandle, "Position");
    attr_texcoord = glGetAttribLocation(programHandle, "TexCoord");
    uniform_mvp = glGetUniformLocation(programHandle, "ModelViewProjection");
    uniform_texture = glGetUniformLocation(programHandle, "Texture");
    
    // Camera
    int w = GetParams().Width;
    int h = GetParams().Height;
    _camera.Init(45.f, (float)w / h, 0.1f, 100.f);
    //_camera.Init(-2,-2, 2,2, 0.1f, 100.f); // Ortho
    _camera.LookAt(glm::vec3(0.0, 2.0, -8.0), glm::vec3(0.0, 0.0, -0.0), glm::vec3(0.0, 1.0, 0.0));
}


void HelloApp::Update()
{
}

void HelloApp::Draw()
{
    _time += 1.f/60.f;
    //float r = fmod(_time, 1.f);
    //glClearColor(0, r, 55.0/255.0, 1.0);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // RENDER
    int w = GetParams().Width;
    int h = GetParams().Height;
    glViewport(0,0, w,h);
    
    // Load matrices
    float angle = _time * 45;
    glm::vec3 axis_y(0, 1, 0);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_y);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -0.0));
    glm::mat4 mvp = _camera.GetMatProj() * _camera.GetMatView() * model * anim;

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set Program + uniforms
    _shader.Begin();
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
    
    // Texture
    _texture.Bind(0);
    glUniform1i(uniform_texture, 0);
    
    // Vertices
    glEnableVertexAttribArray(attr_position);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
    glVertexAttribPointer(attr_position,    // attribute
                          3,                // number of elements per vertex, here (x,y,z)
                          GL_FLOAT,         // the type of each element
                          GL_FALSE,         // take our values as-is
                          0,                // no extra data between each position
                          0                 // offset of first element
                          );
    
    // TexCoords
    glEnableVertexAttribArray(attr_texcoord);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_texcoords);
    glVertexAttribPointer(attr_texcoord,    // attribute
                          2,                // number of elements per vertex, here (x,y)
                          GL_FLOAT,         // the type of each element
                          GL_FALSE,         // take our values as-is
                          0,                // no extra data between each position
                          0                 // offset of first element
                          );
    
    // Index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
    glDisableVertexAttribArray(attr_position);
    glDisableVertexAttribArray(attr_texcoord);
    
    //_texture.Unbind();
    _shader.End();
}
