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
    
    AppQuadBatch(dry::AppParams const &params) : dry::AppiOS(params) { }

    //------------------------------------------------------------------------------------------------
    // OnInit
    //------------------------------------------------------------------------------------------------
    void OnInit()
    {
        Camera.Init(0.f,1.f, 0.f,1.f, 0.1f,10000.f);
        Camera.LookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        QuadBatch.Init(m_Renderer);
        dry::ImageLoader::Load(Texture, dry::GetFilePath("grid.jpg"), dry::Texture::Params(true, false));
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        m_Renderer->Clear(true, true, false);

        QuadBatch.DrawTexture(&Texture, &Camera, glm::mat4(), 0.05f,0.05f, 0.9f,0.9f);
    }

private:
    
    dry::CameraOrthogonal Camera;
    dry::QuadBatch        QuadBatch;
    dry::Texture          Texture;
};
