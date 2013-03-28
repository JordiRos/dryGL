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
        dry::ImageLoader::LoadTextureCube(Texture, dry::GetFilePath("church.jpg"), dry::TextureCube::Params(true, true));
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        GetRenderer()->Clear(true, true, false);
    }

private:
    
    dry::TextureCube Texture;

};
