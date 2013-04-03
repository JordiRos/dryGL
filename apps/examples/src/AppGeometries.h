//
//  AppGeometries.h
//
//  Example: Scene
//

#pragma once

#include "dry.h"
#include "Scene.h"

class AppGeometries : public dry::App
{
public:
    
    AppGeometries(dry::AppParams const &params) : dry::App(params) { }

    //------------------------------------------------------------------------------------------------
    // OnInit
    //------------------------------------------------------------------------------------------------
    void OnInit()
    {
        Camera.Init(45.f, (float)GetParams().Width / GetParams().Height, 0.1f, 10000.f);
        Camera.LookAt(glm::vec3(0.f, 3.f, 4.f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

        // Material
        dry::ImageUtils::Load(Texture1, dry::GetFilePath("tex01.jpg"), dry::Texture::Params(true, true, false));
        dry::ImageUtils::Load(Texture2, dry::GetFilePath("tex02.jpg"), dry::Texture::Params(true, true, false));
        MaterialPlane.Init();
        if (MaterialPlane.GetUniform("Texture0"))
            MaterialPlane.GetUniform("Texture0")->Update(&Texture1, 0);
        MaterialCube.Init();
        if (MaterialCube.GetUniform("Texture0"))
            MaterialCube.GetUniform("Texture0")->Update(&Texture2, 0);

        // Geometries
        dry::GeometryUtils::LoadObj(Cube, dry::GetFilePath("cube.obj"));
        dry::GeometryUtils::CreatePlane(Plane, 2,2, 8,8, glm::vec3(0.f, 1.f, 0.f));

        // Meshes
        MeshPlane.Init(&Plane, &MaterialPlane);
        MeshCube.Init(&Cube, &MaterialCube);
    }

    //------------------------------------------------------------------------------------------------
    // OnDraw
    //------------------------------------------------------------------------------------------------
    void OnDraw()
    {
        m_Renderer->Clear(true, true, false);
        
        float angle = GetTime() * 45.f;
        glm::mat4 rotation = glm::rotate(angle, glm::vec3(0, 1, 0));
        glm::mat4 position = glm::translate(glm::vec3(0.0, 0.0, 0.0));

        MeshPlane.Update();
        MeshPlane.Render(&Camera, glm::mat4());
        MeshCube.Update();
        MeshCube.Render(&Camera, position * rotation);
    }

private:

    dry::CameraPerspective      Camera;
    dry::Texture                Texture1;
    dry::Texture                Texture2;
    dry::Geometry               Cube;
    dry::Geometry               Plane;
    dry::Mesh                   MeshCube;
    dry::Mesh                   MeshPlane;
    dry::MeshMaterialDiffuse    MaterialCube;
    dry::MeshMaterialDiffuse    MaterialPlane;
};
