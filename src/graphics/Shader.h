#ifndef DRY_GRAPHICS_SHADER_H_
#define DRY_GRAPHICS_SHADER_H_

#include "Uniforms.h"

namespace dry {

class Shader
{
public:
	Shader();
	~Shader();

	// TODO: I think we should use r-value and go for Load on constructor
    bool Load(const char *vertex_source, const char *fragment_source);

	void Bind() const;
	UniformInterface* GetUniformByName(const std::string &name);
	unsigned GetAttribByName(const std::string &name);

    bool HasErrors() const
    {
		return !m_Error;
    }
    
	bool IsReady() const
	{
		return m_Program != 0;
	}

	const std::string GetLog() const
	{
		return m_Log;
	}

private:
	bool Compile(const char *source, GLenum type, GLuint &target);
	bool Link();

	void LoadUniforms();
	void LoadAttribs();

	GLuint m_Vertex;
	GLuint m_Fragment;
	GLuint m_Program;
	bool m_Error;

	// TODO: Resource utils
	std::map<std::string, UniformInterface*> m_Uniforms;
	std::map<std::string, unsigned> m_Attribs;
	std::string m_Log;

	DISALLOW_COPY_AND_ASSIGN(Shader);
};

}  // namespace dry

#endif  // DRY_GRAPHICS_SHADER_H_