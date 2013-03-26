//
//  DataType.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {

#define ITEM(e,n,s,g,v,i,a,u) e,
// DataType
enum DataType
{
    #include "DataTypeEnum.h"
    DataTypeCount,
    DataTypeUnknown = 0xFFFFFFFF,
};
#undef ITEM

int  GetDataTypeElements (DataType type);
int  GetDataTypeSize     (DataType type);
int  GetDataTypeGLType   (DataType type);
bool GetDataTypeVbo      (DataType type);
bool GetDataTypeIbo      (DataType type);
bool GetDataTypeAttribute(DataType type);
bool GetDataTypeUniform  (DataType type);

}
