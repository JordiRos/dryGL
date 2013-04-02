//
//  Shader.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_GRAPHICS_SHADER_H_
#define DRY_GRAPHICS_SHADER_H_

namespace dry {
    
class Uniform;
class Attrib;
    
class Shader
{
public:
                        Shader          () { m_Vertex = m_Fragment = m_Program = -1; }
                       ~Shader          () { Free(); }
    
    bool                Init            (const char *vertex, const char *fragment);
    void                Free            ();
    bool                IsOk            () const { return m_Program != 0; }
    
    void                Bind            ();
    void                Unbind          ();
    
    Uniform            *GetUniformByName(const std::string &name);
    Attrib             *GetAttribByName (const std::string &name);

    
private:
    
    void                LogShaderError  (int handle, const std::string &info);
    void                LogProgramError (int handle, const std::string &info);
    
private:
    
    void                LoadUniforms    ();
	void                LoadAttribs     ();

private:
    
    int                 m_Vertex;
    int                 m_Fragment;
    int                 m_Program;
	std::map<std::string, Uniform *>   m_Uniforms;
	std::map<std::string, Attrib *>    m_Attribs;

	DISALLOW_COPY_AND_ASSIGN(Shader);
};

}

#endif
