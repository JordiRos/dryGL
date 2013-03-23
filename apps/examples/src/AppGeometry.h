//
//  AppGeometry.h
//  dryExamples
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//
//  How to use Geometries
//

#include "dry.h"
#include "AppGLSL.h"
#include "ImageLoader.h"
#include "GeometryPlane.h"


class AppGeometry : public dry::AppiOS
{
public:
    
dry::CameraPerspective  Camera;
dry::GeometryPlane      Plane;
dry::ShaderBasic        Shader;
dry::Texture            Texture;


AppGeometry(dry::AppParams const &params) : dry::AppiOS(params)
{
    int w = GetParams().Width;
    int h = GetParams().Height;
    
    Shader.Init();
    Camera.Init(45.f, (float)w / h, 0.1f, 100.f);
    Camera.LookAt(glm::vec3(0.0, 2.0, -8.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    Plane.Init(1, 1, glm::mat4());
    
    dry::ImageLoader::LoadTexture(dry::GetFilePath("metal.png"), Texture);

    GetRenderer()->SetViewport(0,0, w,h);
}


void Draw()
{
    GetRenderer()->Clear(true, true, false);
    GetRenderer()->SetBlendMode(dry::BLEND_ALPHA);
    
    // Bind
    Shader.Bind();
    
    // Matrices
    float angle = GetTimer().GetTime() * 45;
    glm::mat4 anim = glm::rotate(angle, glm::vec3(0, 1, 0));
    glm::mat4 model = glm::translate(glm::vec3(0.0, 0.0, 0.0));
    glm::mat4 mvp = Camera.GetMatProj() * Camera.GetMatView() * model * anim;
    glUniformMatrix4fv(Shader.GetUniformLocation("ModelViewProjection"), 1, GL_FALSE, glm::value_ptr(mvp));

    // Buffers
    Texture.Bind(Shader.GetUniformLocation("Texture"), 0);
    Plane.GetVertices()->Bind(Shader.GetAttribLocation("Position"), false);
    Plane.GetTexCoords0()->Bind(Shader.GetAttribLocation("TexCoord"), false);
    Plane.GetIndices()->Bind();
    
    // Draw
    Plane.GetIndices()->Draw(GL_TRIANGLES);

    // Unbind
    Plane.GetVertices()->Unbind();
    Plane.GetTexCoords0()->Unbind();
    Plane.GetIndices()->Unbind();
    Texture.Unbind();
    Shader.Unbind();
}
    
};
