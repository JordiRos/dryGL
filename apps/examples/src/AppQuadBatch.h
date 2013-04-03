//
//  AppQuadBatch.h
//
//  Example: Load a texture and draw using a QuadBatch object
//

#ifndef APP_QUADBATCH_H_
#define APP_QUADBATCH_H_

#include "dry.h"
#include "QuadBatch.h"

class AppQuadBatch : public dry::App
{
public:
    
    AppQuadBatch(dry::AppParams const &params) : dry::App(params) { }

    //------------------------------------------------------------------------------------------------
    // OnInit
    //------------------------------------------------------------------------------------------------
    void OnInit()
    {
        camera.Init(0.f,1.f, 0.f,1.f, 0.1f,10000.f);
        camera.LookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        quadBatch.Init(m_Renderer);
        dry::ImageUtils::Load(texture, dry::GetFilePath("grid.jpg"), dry::Texture::Params(true, false, false));
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        m_Renderer->Clear(true, true, false);

        quadBatch.DrawTexture(&texture, &camera, glm::mat4(), 0.05f,0.05f, 0.9f,0.9f);
    }

private:
    
    dry::CameraOrthogonal camera;
    dry::QuadBatch        quadBatch;
    dry::Texture          texture;
};

#endif