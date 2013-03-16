//
//  AppSimple.cpp
//  dryExamples
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "AppSimple.h"
#include "../Addons/Renderer/QuadBatch.h"

static dry::CameraPerspective _cameraP;
static dry::CameraOrthogonal _cameraO;

static dry::ShaderBasic _shader;
static dry::Pixels _pixels;
static dry::Texture _texture;
static dry::Fbo _fbo;
static dry::QuadBatch _quads;
static dry::Vbo<float> _vbo_vertices;
static dry::Vbo<float> _vbo_texcoords;

static GLuint attr_position;
static GLuint attr_texcoord;
static GLuint ibo_cube_elements;
static GLuint uniform_mvp;
static GLuint uniform_texture;

static float _time = 0.f;


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
    // TexCoords
    GLfloat cube_texcoords[2*4*6] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
    };
    for (int i = 1; i < 6; i++)
        memcpy(&cube_texcoords[i*4*2], &cube_texcoords[0], 2*4*sizeof(GLfloat));
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
    
    // Vbo
    _vbo_vertices.Init(sizeof(cube_vertices) / sizeof(float), false, 3, cube_vertices);
    _vbo_texcoords.Init(sizeof(cube_texcoords) / sizeof(float), false, 2, cube_texcoords);

    // Ibo
    glGenBuffers(1, &ibo_cube_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
    
    // Texture
    _pixels.InitWithFile(dry::GetFilePath("fire.jpg"));
    _texture.InitWithPixels(_pixels);
    
    // Shader
    _shader.Init();
    attr_position = _shader.GetAttribLocation("Position");
    attr_texcoord = _shader.GetAttribLocation("TexCoord");
    uniform_mvp = _shader.GetUniformLocation("ModelViewProjection");
    uniform_texture = _shader.GetUniformLocation("Texture");
    
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
    GetRenderer()->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, dry::Colorf(0.5f, 0.1f, 0.1f, 1.0f), 1.0f);

    // Draw QuadBatch
    glDisable(GL_DEPTH_TEST);
    _quads.Draw(&_texture, &_cameraO, &_shader, glm::mat4(), 0.f,0.f, w,h);
    glEnable(GL_DEPTH_TEST);

    // Render to FBO
    _fbo.Bind();
    GetRenderer()->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, dry::Colorf(0.1f, 0.9f, 0.1f, 1.0f), 1.0f);
    
    // Alpha blending
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Bind
    _shader.Bind();
    _texture.Bind(uniform_texture, 0);
    _vbo_vertices.Bind(attr_position, false);
    _vbo_texcoords.Bind(attr_texcoord, false);

    // Load matrices
    float angle = _time * 45;
    glm::vec3 axis_y(0, 1, 0);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_y);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -0.0));
    glm::mat4 mvp = _cameraP.GetMatProj() * _cameraP.GetMatView() * model * anim;
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

    // Index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

    // Unbind
    _vbo_vertices.Unbind(attr_position);
    _vbo_texcoords.Unbind(attr_texcoord);
    _texture.Unbind();
    _shader.Unbind();
    _fbo.Unbind();

    // Draw FBO and a texture using QuadBatch
    glDisable(GL_DEPTH_TEST);
    _quads.Draw(&_texture, &_cameraO, &_shader, glm::mat4(), 0,0, w/4.f,h/4.f);
    _quads.Draw(&_fbo, &_cameraO, &_shader, glm::mat4(), w/4.f,h/4.f, w/2.f, h/2.f);
    glEnable(GL_DEPTH_TEST);
}
