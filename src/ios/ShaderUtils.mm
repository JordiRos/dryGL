//
//  ShaderUtils.mm
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#include "dry.h"
#include "ShaderUtils.h"

using namespace dry;


//------------------------------------------------------------------------------------------------
// ReadFileContents
//
//------------------------------------------------------------------------------------------------
static bool ReadFileContents(const std::string &filename, char **buffer)
{
    FILE *file = fopen(filename.c_str(), "r");
    if (file)
    {
        fseek(file, 0, SEEK_END);
        int size = ftell(file);
        fseek(file, 0, SEEK_SET);
        *buffer = NEW_ARRAY(char, size);
        fread(*buffer, 1, size, file);
        (*buffer)[size] = 0;
        fclose(file);
        return true;
    }
    return false;
}


//------------------------------------------------------------------------------------------------
// Load
//
//------------------------------------------------------------------------------------------------
bool ShaderUtils::Load(Shader &shader, const std::string &vs, const std::string &fs)
{
    bool res = false;
    char *bvs = NULL;
    char *bfs = NULL;
    dry::Log(LogInfo, "[ShaderUtils] Load VS from file %s", vs.c_str());
    if (ReadFileContents(vs, &bvs))
    {
        dry::Log(LogInfo, "[ShaderUtils] Load FS from file %s", fs.c_str());
        if (ReadFileContents(fs, &bfs))
            res = shader.Init(bvs, bfs);
        else
            dry::Log(LogWarning, "[ShaderUtils] Can't open FS file %s", fs.c_str());
    }
    else
        dry::Log(LogWarning, "[ShaderUtils] Can't open VS file %s", fs.c_str());
    DISPOSE_ARRAY(bvs);
    DISPOSE_ARRAY(bfs);
    return res;
}
