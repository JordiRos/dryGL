#include "Uniforms.h"

namespace dry {

// Submit specializations
template<>
void Uniform<float>::Submit() const
{
	glUniform1f(m_Location, m_Value);
}

template<>
void Uniform<int>::Submit() const
{
	glUniform1i(m_Location, m_Value);
}

template<>
void Uniform<glm::vec2>::Submit() const
{
	glUniform2fv(m_Location, 1, &m_Value[0]);
}

template<>
void Uniform<glm::vec4>::Submit() const
{
	glUniform4fv(m_Location, 1, &m_Value[0]);
}

template<>
void Uniform<glm::mat4>::Submit() const
{
	glUniformMatrix4fv(m_Location, 1, false, &m_Value[0][0]);
}

UniformInterface* UniformCreate(unsigned type, int location, Shader &shader)
{
	switch(type)
	{
	case GL_FLOAT:
		return new Uniform<float>(location, shader);
	case GL_INT:
	case GL_SAMPLER_2D:
		return new Uniform<int>(location, shader);
	case GL_FLOAT_VEC2:
		return new Uniform<glm::vec2>(location, shader);
	case GL_FLOAT_VEC4:
		return new Uniform<glm::vec4>(location, shader);
	case GL_FLOAT_MAT4:
		return new Uniform<glm::mat4>(location, shader);
	default:
		assert(false);
	}

	return NULL;
}

}  // namespace dry