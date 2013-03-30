//
//  Mesh.cpp
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "Scene.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// Constructor
//
//------------------------------------------------------------------------------------------------
Mesh::Mesh()
{
    Free();
}


//------------------------------------------------------------------------------------------------
// Init
//
//------------------------------------------------------------------------------------------------
bool Mesh::Init(Geometry *geometry, MeshMaterial *material)
{
    bool res = false;
    Free();
    
    if (geometry && material)
    {
        m_Geometry = geometry;
        m_Material = material;
        int maxsize = m_Geometry->GetFaces().size() * 3;
        // Resize attribute buffers
        if (m_Material->GetAttrVertices  ()) m_Material->GetAttrVertices  ()->Resize(maxsize);
        if (m_Material->GetAttrTexCoords0()) m_Material->GetAttrTexCoords0()->Resize(maxsize);
        if (m_Material->GetAttrTexCoords1()) m_Material->GetAttrTexCoords1()->Resize(maxsize);
        if (m_Material->GetAttrTexCoords2()) m_Material->GetAttrTexCoords2()->Resize(maxsize);
        if (m_Material->GetAttrTexCoords3()) m_Material->GetAttrTexCoords3()->Resize(maxsize);
        if (m_Material->GetAttrNormals   ()) m_Material->GetAttrNormals   ()->Resize(maxsize);
        if (m_Material->GetAttrColors    ()) m_Material->GetAttrColors    ()->Resize(maxsize);
        res = true;
    }
    else
        dry::Log(LogWarning, "[Mesh] Mesh needs Geometry and MeshMaterial");
    
    return res;
}


//------------------------------------------------------------------------------------------------
// Free
//
//------------------------------------------------------------------------------------------------
void Mesh::Free()
{
    m_Geometry = NULL;
    m_Material = NULL;
}


//------------------------------------------------------------------------------------------------
// Update
//
//------------------------------------------------------------------------------------------------
void Mesh::Update()
{
    if (IsOk())
    {
        vector<Geometry::Face> &gfaces = m_Geometry->GetFaces();
        // Vertices
        if (m_Geometry->GetUpdateVertices() && m_Material->GetAttrVertices())
        {
            vector<glm::vec3> &gvertices = m_Geometry->GetVertices();
            glm::vec3         *vertices  = (glm::vec3 *)m_Material->GetAttrVertices()->GetData();
            for (int i = 0; i < gfaces.size(); i++)
            {
                vertices[i*3+0] = gvertices[gfaces[i].vtx[0]];
                vertices[i*3+1] = gvertices[gfaces[i].vtx[1]];
                vertices[i*3+2] = gvertices[gfaces[i].vtx[2]];
                /*
                for (int j = 0; j < 3; j++)
                    dry::Log(LogInfo, "[Mesh] Face Vtx %d => %d: %.2f, %.2f, %.2f", i, j, vertices[i*3+j].x, vertices[i*3+j].y, vertices[i*3+j].z);
                 */
            }
            m_Material->GetAttrVertices()->Update(false);
            m_Geometry->UpdateVertices(false);
        }
        // TexCoords0
        if (m_Geometry->GetUpdateTexCoords0() && m_Material->GetAttrTexCoords0())
        {
            vector<glm::vec2> &gtexcoords0 = m_Geometry->GetTexCoords0();
            glm::vec2         *texcoords0  = (glm::vec2 *)m_Material->GetAttrTexCoords0()->GetData();
            for (int i = 0; i < gfaces.size(); i++)
            {
                texcoords0[i*3+0] = gtexcoords0[gfaces[i].uv0[0]];
                texcoords0[i*3+1] = gtexcoords0[gfaces[i].uv0[1]];
                texcoords0[i*3+2] = gtexcoords0[gfaces[i].uv0[2]];
                /*
                for (int j = 0; j < 3; j++)
                    dry::Log(LogInfo, "[Mesh] Face Tex0 %d => %d: %.2f, %.2f", i, j, texcoords0[i*3+j].x, texcoords0[i*3+j].y);
                 */
            }
            m_Material->GetAttrTexCoords0()->Update(false);
            m_Geometry->UpdateTexCoords0(false);
        }
        // TexCoords1
        if (m_Geometry->GetUpdateTexCoords1() && m_Material->GetAttrTexCoords1())
        {
            vector<glm::vec2> &gtexcoords1 = m_Geometry->GetTexCoords1();
            glm::vec2         *texcoords1  = (glm::vec2 *)m_Material->GetAttrTexCoords1()->GetData();
            for (int i = 0; i < gfaces.size(); i++)
            {
                texcoords1[i*3+0] = gtexcoords1[gfaces[i].uv1[0]];
                texcoords1[i*3+1] = gtexcoords1[gfaces[i].uv1[1]];
                texcoords1[i*3+2] = gtexcoords1[gfaces[i].uv1[2]];
                /*
                for (int j = 0; j < 3; j++)
                    dry::Log(LogInfo, "[Mesh] Face Tex1 %d => %d: %.2f, %.2f", i, j, texcoords1[i*3+j].x, texcoords1[i*3+j].y);
                 */
            }
            m_Material->GetAttrTexCoords1()->Update(false);
            m_Geometry->UpdateTexCoords1(false);
        }
        // TexCoords2
        if (m_Geometry->GetUpdateTexCoords2() && m_Material->GetAttrTexCoords2())
        {
            vector<glm::vec2> &gtexcoords2 = m_Geometry->GetTexCoords2();
            glm::vec2         *texcoords2  = (glm::vec2 *)m_Material->GetAttrTexCoords2()->GetData();
            for (int i = 0; i < gfaces.size(); i++)
            {
                texcoords2[i*3+0] = gtexcoords2[gfaces[i].uv2[0]];
                texcoords2[i*3+1] = gtexcoords2[gfaces[i].uv2[1]];
                texcoords2[i*3+2] = gtexcoords2[gfaces[i].uv2[2]];
                /*
                for (int j = 0; j < 3; j++)
                    dry::Log(LogInfo, "[Mesh] Face Tex2 %d => %d: %.2f, %.2f", i, j, texcoords2[i*3+j].x, texcoords2[i*3+j].y);
                 */
            }
            m_Material->GetAttrTexCoords2()->Update(false);
            m_Geometry->UpdateTexCoords2(false);
        }
        // TexCoords3
        if (m_Geometry->GetUpdateTexCoords3() && m_Material->GetAttrTexCoords3())
        {
            vector<glm::vec2> &gtexcoords3 = m_Geometry->GetTexCoords3();
            glm::vec2         *texcoords3  = (glm::vec2 *)m_Material->GetAttrTexCoords3()->GetData();
            for (int i = 0; i < gfaces.size(); i++)
            {
                texcoords3[i*3+0] = gtexcoords3[gfaces[i].uv3[0]];
                texcoords3[i*3+1] = gtexcoords3[gfaces[i].uv3[1]];
                texcoords3[i*3+2] = gtexcoords3[gfaces[i].uv3[2]];
                /*
                for (int j = 0; j < 3; j++)
                    dry::Log(LogInfo, "[Mesh] Face Tex3 %d => %d: %.2f, %.2f", i, j, texcoords3[i*3+j].x, texcoords3[i*3+j].y);
                 */
            }
            m_Material->GetAttrTexCoords3()->Update(false);
            m_Geometry->UpdateTexCoords3(false);
        }
        // Normals
        if (m_Geometry->GetUpdateNormals() && m_Material->GetAttrNormals())
        {
            vector<glm::vec3> &gnormals = m_Geometry->GetNormals();
            glm::vec3         *normals  = (glm::vec3 *)m_Material->GetAttrNormals()->GetData();
            for (int i = 0; i < gfaces.size(); i++)
            {
                normals[i*3+0] = gnormals[gfaces[i].nor[0]];
                normals[i*3+1] = gnormals[gfaces[i].nor[1]];
                normals[i*3+2] = gnormals[gfaces[i].nor[2]];
                /*
                for (int j = 0; j < 3; j++)
                    dry::Log(LogInfo, "[Mesh] Face Norm %d => %d: %.2f, %.2f, %.2f", i, j, normals[i*3+j].x, normals[i*3+j].y, normals[i*3+j].z);
                 */
            }
            m_Material->GetAttrNormals()->Update(false);
            m_Geometry->UpdateNormals(false);
        }
        // Colors
        if (m_Geometry->GetUpdateColors() && m_Material->GetAttrColors())
        {
            vector<glm::vec4> &gcolors = m_Geometry->GetColors();
            glm::vec4         *colors  = (glm::vec4 *)m_Material->GetAttrColors()->GetData();
            for (int i = 0; i < gfaces.size(); i++)
            {
                colors[i*3+0] = gcolors[gfaces[i].col[0]];
                colors[i*3+1] = gcolors[gfaces[i].col[1]];
                colors[i*3+2] = gcolors[gfaces[i].col[2]];
                /*
                for (int j = 0; j < 3; j++)
                    dry::Log(LogInfo, "[Mesh] Face Col %d => %d: %.2f, %.2f, %.2f, %.2f", i, j, colors[i*3+j].r, colors[i*3+j].g, colors[i*3+j].b, colors[i*3+j].a);
                 */
            }
            m_Material->GetAttrColors()->Update(false);
            m_Geometry->UpdateColors(false);
        }
    }
}


//------------------------------------------------------------------------------------------------
// Render
//
//------------------------------------------------------------------------------------------------
void Mesh::Render(Camera const *camera, glm::mat4 const &model)
{
    if (IsOk())
    {
        // Update
        if (m_Material->GetUniformModel     ()) m_Material->GetUniformModel     ()->Update(model);
        if (m_Material->GetUniformView      ()) m_Material->GetUniformView      ()->Update(camera->GetMatView());
        if (m_Material->GetUniformProjection()) m_Material->GetUniformProjection()->Update(camera->GetMatProjection());
        
        // Bind
        m_Material->Bind();
        glDrawArrays(GL_TRIANGLES, 0, m_Geometry->GetFaces().size() * 3);
        m_Material->Unbind();
    }
}
