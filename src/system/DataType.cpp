//
//  DataType.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "DataType.h"

using namespace dry;


struct DataTypeInfo
{
    int  Elements;
    int  Size;
    int  GLVar;
    int  GLType;
    bool Vbo;
    bool Ibo;
};

// DataTypeInfo
#define ITEM(e,n,s,g,t,v,i) { n,s,g,t,v,i },
static DataTypeInfo s_DataTypeInfo[DataTypeCount] = {
#include "DataTypeEnum.h"
};
#undef ITEM

static bool DataTypeValid(DataType type)
{
    return ((int)type >= 0 && type < DataTypeCount);
}

int dry::GetDataTypeElements(DataType type)
{
    return DataTypeValid(type) ? s_DataTypeInfo[type].Elements : 0;
}

int dry::GetDataTypeSize(DataType type)
{
    return DataTypeValid(type) ? s_DataTypeInfo[type].Size : 0;
}

int dry::GetDataTypeGLVar(DataType type)
{
    return DataTypeValid(type) ? s_DataTypeInfo[type].GLVar : 0;
}

int dry::GetDataTypeGLType(DataType type)
{
    return DataTypeValid(type) ? s_DataTypeInfo[type].GLType : 0;
}

bool dry::GetDataTypeVbo(DataType type)
{
    return DataTypeValid(type) ? s_DataTypeInfo[type].Vbo : false;
}

bool dry::GetDataTypeIbo(DataType type)
{
    return DataTypeValid(type) ? s_DataTypeInfo[type].Ibo : false;
}
