//
//  AppQuadBatch.h
//
//  Example: Load a texture and draw using a QuadBatch object
//

#pragma once

#include "dry.h"
#include "QuadBatch.h"

class AppQuadBatch : public dry::AppiOS
{
public:

dry::CameraOrthogonal Camera;
dry::QuadBatch        QuadBatch;
dry::Texture          Texture;

AppQuadBatch(dry::AppParams const &params) : dry::AppiOS(params) { }

void Init()
{
    Camera.Init(0,1, 0,1, 0.1f,10000.f);
    Camera.LookAt(glm::vec3(0.0, 0.0, 1.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    QuadBatch.Init(GetRenderer());
    dry::ImageLoader::LoadTexture(Texture, dry::GetFilePath("grid.jpg"), dry::Texture::Params(true, false));
}

void Draw()
{
    GetRenderer()->Clear(true, true, false);

    QuadBatch.DrawTexture(&Texture, &Camera, glm::mat4(), 0.1f,0.1f, 0.8f,0.8f);
}

};
