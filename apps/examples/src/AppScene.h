//
//  AppScene.h
//
//  Example: Loading and drawing a TextureCube
//

#pragma once

#include "dry.h"
#include "Geometry.h"
#include "GeometryLoader.h"

class AppScene : public dry::AppiOS
{
public:
    
AppScene(dry::AppParams const &params) : dry::AppiOS(params) { }

void OnInit()
{
    Shader.Init();
    Material.Init(&Shader);
    dry::GeometryLoader::LoadGeometry(Geometry, dry::GetFilePath("cube.obj"));
}

void OnDraw()
{
    GetRenderer()->Clear(true, true, false);
}

private:

    dry::ShaderBasic    Shader;
    dry::Material       Material;
    dry::Geometry       Geometry;
};
