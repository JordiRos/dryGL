//
//  AppSimple
//  dryExamples
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "AppSimple.h"
#include "../Addons/Renderer/QuadBatch.h"

dry::CameraPerspective _cameraP;
dry::CameraOrthogonal _cameraO;

dry::ShaderBasic _shader;
dry::Pixels _pixels;
dry::Texture _texture;
dry::Fbo _fbo;
dry::QuadBatch _quads;

GLuint attr_position;
GLuint attr_texcoord;
GLuint vbo_cube_vertices;
GLuint vbo_cube_texcoords;
GLuint ibo_cube_elements;
GLuint uniform_mvp;
GLuint uniform_texture;

float _time = 0.f;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
void AppSimple::Init()
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
    _pixels.InitWithFile(dry::GetFilePath("fire.jpg"));
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
    
    // Perspective
    _cameraP.Init(45.f, (float)w / h, 0.1f, 100.f);
    _cameraP.LookAt(glm::vec3(0.0, 2.0, -8.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    
    // Orthogonal
    _cameraO.Init(0,w, 0,h, -1.f,1.f);
    _cameraO.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    
    // Fbo
    dry::Fbo::Params params;
    params.Width  = w;
    params.Height = h;
    _fbo.Init(params);
    
    // QuadBatch
    _quads.Init();
    
    // RENDER
    glViewport(0,0, w,h);
}


//------------------------------------------------------------------------------------------------
// Update
//
//------------------------------------------------------------------------------------------------
void AppSimple::Update()
{
    _time += 1.f/60.f;
}


//------------------------------------------------------------------------------------------------
// Draw
//
//------------------------------------------------------------------------------------------------
void AppSimple::Draw()
{
    int w = GetParams().Width;
    int h = GetParams().Height;

    //float r = fmod(_time, 1.f);
    //glClearColor(0, r, 55.0/255.0, 1.0f);
    glClearColor(0.5f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw QuadBatch
    glDisable(GL_DEPTH_TEST);
    _quads.Draw(&_texture, &_cameraO, _shader.GetShader(), glm::mat4(), 0.f,0.f, w,h);
    glEnable(GL_DEPTH_TEST);

    // Render to FBO
    _fbo.Bind();
    glClearColor(0.1f, 0.9f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Load matrices
    float angle = _time * 45;
    glm::vec3 axis_y(0, 1, 0);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_y);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -0.0));
    glm::mat4 mvp = _cameraP.GetMatProj() * _cameraP.GetMatView() * model * anim;

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set Program + uniforms
    _shader.GetShader()->Bind();
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
    
    // Texture
    _texture.Bind();
    glActiveTexture(GL_TEXTURE0);
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
    
    _texture.Unbind();
    _shader.GetShader()->Unbind();
    
    _fbo.Unbind();

    // Draw FBO and a texture using QuadBatch
    glDisable(GL_DEPTH_TEST);
    _quads.Draw(&_texture, &_cameraO, _shader.GetShader(), glm::mat4(), 0,0, w/4.f,h/4.f);
    _quads.Draw(&_fbo, &_cameraO, _shader.GetShader(), glm::mat4(), w/4.f,h/4.f, w/2.f, h/2.f);
    glEnable(GL_DEPTH_TEST);
}
