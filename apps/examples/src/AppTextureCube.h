//
//  AppTextureCube.h
//
//  Example: Loading and drawing a TextureCube
//

#pragma once

#include "dry.h"
#include "QuadBatch.h"

class AppTextureCube : public dry::AppiOS
{
public:

dry::TextureCube Texture;
    
AppTextureCube(dry::AppParams const &params) : dry::AppiOS(params) { }

void OnInit()
{
    dry::ImageLoader::LoadTextureCube(Texture, dry::GetFilePath("church.jpg"), dry::TextureCube::Params(true, true));
}

void OnDraw()
{
    GetRenderer()->Clear(true, true, false);

    //QuadBatch.DrawTexture(&Texture, &CameraP, anim, -0.5,-0.5, 1.f,1.f);
}

};
