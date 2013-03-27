//
//  DataTypeEnum.h
//
//  DataType#Enum, Elements, DataSize, GLType, Vbo, Ibo, Attribute, Uniform
//

ITEM(DataTypeByte,     1,  sizeof(char),       GL_BYTE,           true,  true,  true,  false)
ITEM(DataTypeUByte,    1,  sizeof(char),       GL_UNSIGNED_BYTE,  true,  true,  true,  false)
ITEM(DataTypeShort,    1,  sizeof(short),      GL_SHORT,          true,  true,  true,  false)
ITEM(DataTypeUShort,   1,  sizeof(short),      GL_UNSIGNED_SHORT, true,  true,  true,  false)
ITEM(DataTypeInt,      1,  sizeof(int),        GL_INT,            true,  true,  true,  true)
ITEM(DataTypeUInt,     1,  sizeof(int),        GL_UNSIGNED_INT,   true,  true,  true,  false)
ITEM(DataTypeFloat,    1,  sizeof(float),      GL_FLOAT,          true,  false, true,  true)
ITEM(DataTypeVec2,     2,  sizeof(float) * 2,  GL_FLOAT,          true,  false, true,  true)
ITEM(DataTypeVec3,     3,  sizeof(float) * 3,  GL_FLOAT,          true,  false, true,  true)
ITEM(DataTypeVec4,     4,  sizeof(float) * 4,  GL_FLOAT,          true,  false, true,  true)
ITEM(DataTypeMat2,     4,  sizeof(float) * 4,  GL_FLOAT,          true,  false, true,  true)
ITEM(DataTypeMat3,     9,  sizeof(float) * 9,  GL_FLOAT,          true,  false, true,  true)
ITEM(DataTypeMat4,     16, sizeof(float) * 16, GL_FLOAT,          true,  false, true,  true)
ITEM(DataTypeTex2D,    1,  0,                  0,                 false, false, false, true)
ITEM(DataTypeTexCube, 1,  0,                  0,                 false, false, false, true)
ITEM(DataTypeFboColor, 1,  0,                  0,                 false, false, false, true)
ITEM(DataTypeFboDepth, 1,  0,                  0,                 false, false, false, true)
