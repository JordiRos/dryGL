//
//  Shader.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class Shader
{
public:
                Shader          () { m_HandleVS = -1; m_HandleFS = -1; m_HandleProgram = -1; }
               ~Shader          () { Free(); }

    bool        InitWithFile    (const string &vs, const string &fs);
    bool        InitWithProgram (const string &vs, const string &fs);
    void        Free            ();
    
    void        Bind            ();
    void        Unbind          ();
    
    int         GetHandleProgram() const { return m_HandleProgram; }

private:

    void        LogShaderError  (int handle, const string &info);
    void        LogProgramError (int handle, const string &info);

private:

    int         m_HandleVS;
    int         m_HandleFS;
    int         m_HandleProgram;
};

}