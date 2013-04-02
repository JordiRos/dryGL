//
//  DataType.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_SYSTEM_DATATYPE_H_
#define DRY_SYSTEM_DATATYPE_H_

namespace dry {

#define ITEM(e,n,s,g,t,v,i,a,u) e,
// DataType
enum DataType
{
    #include "DataTypeEnum.h"
    DataTypeCount,
    DataTypeUnknown = 0xFFFFFFFF,
};
#undef ITEM

// DataType info
int         GetDataTypeElements    (DataType type);
int         GetDataTypeSize        (DataType type);
int         GetDataTypeGLVar       (DataType type);
int         GetDataTypeGLType      (DataType type);
bool        GetDataTypeVbo         (DataType type);
bool        GetDataTypeIbo         (DataType type);
bool        GetDataTypeAttribute   (DataType type);
bool        GetDataTypeUniform     (DataType type);

// Inverse
DataType    GetDataTypeWithGLType  (int glType);

}

#endif