#include "Shader.h"

namespace dry {

Shader::Shader(const char *vertex_source, const char *pixel_source)
	: m_Vertex(0), m_Fragment(0), m_Program(0), m_Error(false)
{
	bool vertex = Compile(vertex_source, GL_VERTEX_SHADER, m_Vertex);
	bool fragment = Compile(vertex_source, GL_VERTEX_SHADER, m_Vertex);

	if (!vertex || !fragment) {
		m_Error = true;
		return;
	}

	bool link = Link();

	if (!link) {
		m_Error = true;
		return;
	}

    if (IsReady()) {
        LoadUniforms();
        LoadAttribs();
    }
}

bool Shader::Compile(const char *source, GLenum type, GLuint &target) {
	target = glCreateShader(type);

	glShaderSource(target, 1, &vertex_source, NULL);
	glCompileShader(target);

	// Check compile errors
	GLint error;
	glGetShaderiv(target, GL_COMPILE_STATUS, &error);
	if (error == GL_FALSE)
	{
		GLsizei length;
		glGetShaderiv(target, GL_INFO_LOG_LENGTH, &length);

		std::string log(length);
		glGetShaderInfoLog(target, length, NULL, &log[0]);
		m_Log += log;

		return false;
	}

	return true;
}

bool Shader::Link() {
	m_Program = glCreateProgram();

	glAttachShader(m_Program, m_Vertex);
	glAttachShader(m_Program, m_Fragment);

	// Link
	glLinkProgram(m_Program);

	// Check for errors
	GLint error;
	glGetProgramiv(program, GL_LINK_STATUS, &error);
	if (error == GL_FALSE)
	{
		m_Error = true;
		
		GLsizei length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

		std::string log(length);
		glGetProgramInfoLog(program, length, NULL, &log[0]);
		m_Log += log;

		return false;
	}

	return true;
}

void Shader::LoadUniforms() 
{
    GLint amount;
    glGetProgramiv(m_Program, GL_ACTIVE_UNIFORMS, &amount);

    GLint nameLenght;
    glGetProgramiv(m_Program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &longName);
    std::string name(nameLenght);

    GLint size;
    GLenum type;
    GLsizei length;
    for(int index = 0; index < amount; ++index)
    {
        glGetActiveUniform(m_Program, index, 1024, &length, &size, &type, &name[0]);
        m_Uniforms[name] = UniformCreate(type, glGetUniformLocation(m_Program, name), *this);
    }
}
	
void Shader::LoadAttribs() 
{
    GLint amount;
    glGetProgramiv(m_Program, GL_ACTIVE_ATTRIBUTES, &amount);

    GLint nameLenght;
    glGetProgramiv(m_Program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &longName);
    std::string name(nameLenght);
    
    GLint size;
    GLenum type;
    GLsizei length;
    for(int index = 0; index < amount; ++index)
    {
        m_Attribs[name] = UniformCreate(type, glGetUniformLocation(m_Program, name), *this);
    }
}



Shader::~Shader()
{
	glDeleteShader(m_Vertex);
	glDeleteShader(m_Fragment);
	glDeleteProgram(m_Program);
}

UniformInterface* Shader::GetUniformByName(const std::string &name)
{
	auto target = m_Uniforms.find(name);
	if(target == m_Uniforms.end())
		return NULL;
	return target->second;            
}

unsigned Shader::GetAttribByName(const std::string &name);
{
	auto target = m_Attribs.find(name);
	if(target == m_Attribs.end())
		return NULL;
	return target->second;            
}

void Bind() const
{
	glUseProgram(m_Program);
	// TODO:  dirty uniforms vector instead of all uniforms on map
	for(auto it = m_Uniforms.begin(); it != m_Uniforms.end(); ++it)
		it->second->Submit();
}

}  // namespace dry