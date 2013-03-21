//
//  AppVbo.cpp
//  dryExamples
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//
//  dryGL: Simple usage of Vbo/Ibo buffers for rendering geometry using a shader as material
//

#include "dry.h"
#include "AppVbo.h"
#include "ImageLoader.h"
#include "QuadBatch.h"

static dry::CameraPerspective _camera;
static dry::CameraOrthogonal _cameraO;
static dry::ShaderBasic _shader;
static dry::Texture _texture;
static dry::Vbo<glm::vec3> _vbo_vertices;
static dry::Vbo<glm::vec2> _vbo_texcoords;
static dry::Ibo<ushort> _ibo_elements;
static dry::QuadBatch _quads;

//------------------------------------------------------------------------------------------------
// Constructor
//
//------------------------------------------------------------------------------------------------
AppVbo::AppVbo(dry::AppParams const &params) : dry::AppiOS(params)
{
    // Vertices
    GLfloat vertices[] = {
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
    GLfloat texcoords[2*4*6] = {
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
    };
    for (int i = 1; i < 6; i++)
        memcpy(&texcoords[i*4*2], &texcoords[0], 2*4*sizeof(GLfloat));
    // Indices
    GLushort indices[] = {
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
    _vbo_vertices.Init(24, false, 3, (glm::vec3 *)vertices);
    _vbo_texcoords.Init(24, false, 2, (glm::vec2 *)texcoords);
    // Ibo
    _ibo_elements.Init(36, false, indices);
    
    // Texture
    string file = dry::GetFilePath("metal.png");
    dry::ImageLoader::LoadTexture(file, _texture);
    
    // Shader
    _shader.Init();
    
    // Camera
    int w = GetParams().Width;
    int h = GetParams().Height;
    _camera.Init(45.f, (float)w / h, 0.1f, 100.f);
    _camera.LookAt(glm::vec3(0.0, 2.0, -8.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    // Orthogonal
    _cameraO.Init(0,w, 0,h, -1.f,1.f);
    _cameraO.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

    // QuadBatch
    _quads.Init();

    // Viewport
    GetRenderer()->SetViewport(0,0, w,h);
}


//------------------------------------------------------------------------------------------------
// Update
//
//------------------------------------------------------------------------------------------------
void AppVbo::Update(float time, float delta)
{
}


//------------------------------------------------------------------------------------------------
// Draw
//
//------------------------------------------------------------------------------------------------
void AppVbo::Draw()
{
    int w = GetParams().Width;
    int h = GetParams().Height;

    GetRenderer()->Clear(true, true, false);
    GetRenderer()->SetBlendMode(dry::BLEND_ALPHA);
    
    // Locations
    int attr_position = _shader.GetAttribLocation("Position");
    int attr_texcoord = _shader.GetAttribLocation("TexCoord");
    int uniform_mvp = _shader.GetUniformLocation("ModelViewProjection");
    int uniform_texture = _shader.GetUniformLocation("Texture");

     // Bind
    _shader.Bind();
    _texture.Bind(uniform_texture, 0);
    _vbo_vertices.Bind(attr_position, false);
    _vbo_texcoords.Bind(attr_texcoord, false);
    _ibo_elements.Bind();
    
    // Load matrices
    float angle = GetTimer().GetTime() * 45;
    glm::mat4 anim = glm::rotate(angle, glm::vec3(0, 1, 0));
    glm::mat4 model = glm::translate(glm::vec3(0.0, 0.0, 0.0));
    glm::mat4 mvp = _camera.GetMatProj() * _camera.GetMatView() * model * anim;
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

    // Draw!
    _ibo_elements.Draw(GL_TRIANGLES);

    // Unbind
    _vbo_vertices.Unbind();
    _vbo_texcoords.Unbind();
    _ibo_elements.Unbind();
    _texture.Unbind();
    _shader.Unbind();
    
    // Draw QuadBatch
    glDisable(GL_DEPTH_TEST);
    _quads.DrawTexture(&_texture, &_cameraO, model, 0,0,w,h);
    glEnable(GL_DEPTH_TEST);

}
