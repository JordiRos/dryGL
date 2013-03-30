//
//  Mesh.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

class Geometry;
class MeshMaterial;

class Mesh
{
public:
                    Mesh            ();
                   ~Mesh            () { Free(); }
    
    bool            Init            (Geometry *geometry, MeshMaterial *material);
    void            Free            ();
    bool            IsOk            () { return m_Geometry && m_Material; }
    
    void            Update          ();
    void            Render          (Camera const *camera, glm::mat4 const &model);
    
    void            SetMaterial     (MeshMaterial *material);

protected:

    Geometry       *m_Geometry;
    MeshMaterial   *m_Material;
};
    
}
