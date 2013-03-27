//
//  DataTypeEnum.h
//
//  DataType#Enum, Elements, DataSize, GLVarType, GLType, Vbo, Ibo, Attribute, Uniform
//

ITEM(DataTypeUByte,    1,  sizeof(uchar),      GL_UNSIGNED_BYTE,  0,                true,  true,  true,  false)
ITEM(DataTypeUShort,   1,  sizeof(ushort),     GL_UNSIGNED_SHORT, 0,                true,  true,  true,  false)
ITEM(DataTypeUInt,     1,  sizeof(uint),       GL_UNSIGNED_INT,   0,                true,  true,  true,  false)
ITEM(DataTypeByte,     1,  sizeof(char),       GL_BYTE,           0,                true,  true,  true,  false)
ITEM(DataTypeShort,    1,  sizeof(short),      GL_SHORT,          0,                true,  true,  true,  false)
ITEM(DataTypeInt,      1,  sizeof(int),        GL_INT,            GL_INT,           true,  true,  true,  true)
ITEM(DataTypeFloat,    1,  sizeof(float),      GL_FLOAT,          GL_FLOAT,         true,  false, true,  true)
ITEM(DataTypeVec2,     2,  sizeof(float) * 2,  GL_FLOAT,          GL_FLOAT_VEC2,    true,  false, true,  true)
ITEM(DataTypeVec3,     3,  sizeof(float) * 3,  GL_FLOAT,          GL_FLOAT_VEC3,    true,  false, true,  true)
ITEM(DataTypeVec4,     4,  sizeof(float) * 4,  GL_FLOAT,          GL_FLOAT_VEC4,    true,  false, true,  true)
ITEM(DataTypeMat2,     4,  sizeof(float) * 4,  GL_FLOAT,          GL_FLOAT_MAT2,    true,  false, true,  true)
ITEM(DataTypeMat3,     9,  sizeof(float) * 9,  GL_FLOAT,          GL_FLOAT_MAT3,    true,  false, true,  true)
ITEM(DataTypeMat4,     16, sizeof(float) * 16, GL_FLOAT,          GL_FLOAT_MAT4,    true,  false, true,  true)
ITEM(DataTypeTex2D,    1,  0,                  0,                 GL_SAMPLER_2D,    false, false, false, true)
ITEM(DataTypeTexCube,  1,  0,                  0,                 GL_SAMPLER_CUBE,  false, false, false, true)
