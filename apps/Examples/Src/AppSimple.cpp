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

static dry::ShaderBasic _shader;
static dry::Pixels _pixels;
static dry::Texture _texture;
static dry::Vbo<glm::vec3> _vbo_vertices;
static dry::Vbo<glm::vec2> _vbo_texcoords;
static dry::Ibo<ushort> _ibo_elements;
static dry::QuadBatch _quads;

static GLuint attr_position;
static GLuint attr_texcoord;
static GLuint uniform_mvp;
static GLuint uniform_texture;


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
void AppSimple::Init()
{
    AppiOS::Init();
    
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
    _vbo_vertices.Init(sizeof(cube_vertices) / 3*sizeof(GLfloat), false, 3, (glm::vec3 *)cube_vertices);
    _vbo_texcoords.Init(sizeof(cube_texcoords) / 2*sizeof(GLfloat), false, 2, (glm::vec2 *)cube_texcoords);
    // Ibo
    _ibo_elements.Init(sizeof(cube_elements) / sizeof(GLushort), false, cube_elements);
    
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
    
    // QuadBatch
    _quads.Init();

    // Viewport
    GetRenderer()->SetViewport  (0,0, w,h);
    GetRenderer()->SetClearColor(dry::Colorf(0.5f, 0.5f, 0.5f, 1.0f), 1.0f, 0);
}


//------------------------------------------------------------------------------------------------
// Update
//
//------------------------------------------------------------------------------------------------
void AppSimple::Update()
{
}


//------------------------------------------------------------------------------------------------
// Draw
//
//------------------------------------------------------------------------------------------------
void AppSimple::Draw()
{
    glEnable(GL_DEPTH_TEST);

    GetRenderer()->Clear(true, true, false);
    GetRenderer()->SetBlendMode(dry::BLEND_ALPHA);
    
    // Bind
    _shader.Bind();
    _texture.Bind(uniform_texture, 0);
    _vbo_vertices.Bind(attr_position, false);
    _vbo_texcoords.Bind(attr_texcoord, false);
    _ibo_elements.Bind();
    
    // Load matrices
    float angle = GetTimer().GetTime() * 45;
    glm::vec3 axis_y(0, 1, 0);
    glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_y);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -0.0));
    glm::mat4 mvp = _cameraP.GetMatProj() * _cameraP.GetMatView() * model * anim;
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

    // Draw!
    _ibo_elements.Draw(GL_TRIANGLES);

    // Unbind
    _vbo_vertices.Unbind(attr_position);
    _vbo_texcoords.Unbind(attr_texcoord);
    _ibo_elements.Unbind();
    _texture.Unbind();
    _shader.Unbind();
}
