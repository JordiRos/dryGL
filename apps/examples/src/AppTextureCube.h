//
//  AppTextureCube.h
//
//  Example: Loading a TextureCube
//

#pragma once

#include "dry.h"
#include "QuadBatch.h"

class AppTextureCube : public dry::AppiOS
{
public:

    AppTextureCube(dry::AppParams const &params) : dry::AppiOS(params) { }

    //------------------------------------------------------------------------------------------------
    // OnInit
    //------------------------------------------------------------------------------------------------
    void OnInit()
    {
        dry::ImageUtils::Load(Texture, dry::GetFilePath("church.jpg"), dry::TextureCube::Params(true, true, false));
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        m_Renderer->Clear(true, true, false);
    }

private:
    
    dry::TextureCube Texture;

};
