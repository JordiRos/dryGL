#ifndef DRY_GRAPHICS_SHADER_H_
#define DRY_GRAPHICS_SHADER_H_

#include "Uniforms.h"

namespace dry {

class Shader
{
public:
	// TODO: Inconsistent with GetUniformBynName (std::string vs const char*)
	Shader(const char *vertex_source, const char *pixel_source);
	~Shader();

	void Bind() const;
	UniformInterface* GetUniformByName(const std::string &name);
	unsigned GetAttribByName(const std::string &name);

	bool IsReady() const
	{
		return !m_Error;
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