//
//  Mesh.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

#include "Geometry.h"

namespace dry {
    
class Mesh
{
public:
                    Mesh            () { m_Geometry = NULL; m_Material = NULL; }
                   ~Mesh            () { Free(); }
    
    bool            Init            (Geometry *geometry, Material *material);
    void            Free            ();

    void            Update          ();
    void            Draw            ();
    
    void            UpdateVertices  () { m_UpdateVertices   = true; }
    void            UpdateTexCoords0() { m_UpdateTexCoords0 = true; }
    void            UpdateTexCoords1() { m_UpdateTexCoords1 = true; }
    void            UpdateTexCoords2() { m_UpdateTexCoords2 = true; }
    void            UpdateTexCoords3() { m_UpdateTexCoords3 = true; }
    void            UpdateNormals   () { m_UpdateNormals    = true; }
    void            UpdateColors    () { m_UpdateColors     = true; }
    void            UpdateIndices   () { m_UpdateIndices    = true; }

    Geometry       *GetGeometry     () { return m_Geometry; }
    
protected:

    Geometry       *m_Geometry;
    Material       *m_Material;
    bool            m_UpdateVertices;
    bool            m_UpdateTexCoords0;
    bool            m_UpdateTexCoords1;
    bool            m_UpdateTexCoords2;
    bool            m_UpdateTexCoords3;
    bool            m_UpdateNormals;
    bool            m_UpdateColors;
    bool            m_UpdateIndices;
};
    
}
