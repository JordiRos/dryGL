//
//  AppScene.h
//
//  Example: Scene
//

#pragma once

#include "dry.h"
#include "Scene.h"

class AppScene : public dry::AppiOS
{
public:
    
    AppScene(dry::AppParams const &params) : dry::AppiOS(params) { }

    //------------------------------------------------------------------------------------------------
    // OnInit
    //------------------------------------------------------------------------------------------------
    void OnInit()
    {
        Camera.Init(45.f, (float)GetParams().Width / GetParams().Height, 0.1f, 10000.f);
        Camera.LookAt(glm::vec3(4.f, 0.f, 0.f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

        // Material
        dry::ImageLoader::Load(Texture, dry::GetFilePath("grid.jpg"), dry::Texture::Params(true, true));
        Material.Init();
        if (Material.GetUniform("Texture0"))
            Material.GetUniform("Texture0")->Update(&Texture, 0);

        // Geometries
        //dry::GeometryLoader::LoadGeometry(Cube, dry::GetFilePath("cube.obj"));
        Plane.Init(2,2, 8,8, glm::vec3(1.f, 0.f, 0.f));

        // Meshes
        //MeshCube.Init(&Cube, &Material);
        MeshPlane.Init(&Plane, &Material);
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        m_Renderer->Clear(true, true, false);
        
        glm::mat4 model = glm::translate(glm::vec3(0.0, 0.0, 0.0));

        MeshPlane.Update();
        MeshPlane.Render(&Camera, model);
    }

private:

    dry::CameraPerspective      Camera;
    dry::Texture                Texture;
    dry::GeometryPlane          Plane;
    dry::Mesh                   MeshPlane;
    dry::MeshMaterialDiffuse    Material;
};
