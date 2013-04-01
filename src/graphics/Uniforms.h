#ifndef DRY_GRAPHICS_UNIFORM_H_
#define DRY_GRAPHICS_UNIFORM_H_

// TODO: Include policiy?
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

namespace dry {

class Shader;
template<typename T> class Uniform;

class UniformInterface
{
public:
	virtual ~UniformInterface() 
	{}

	template<typename T>
	void Update(const T &new_value)
	{
		(static_cast<Uniform<T>*>(this))->Update(new_value);
	}

	virtual void Submit() const = 0;
};

template<typename T>
class Uniform : public UniformInterface
{
public:
	Uniform(unsigned location, Shader &parent) : m_Location(location), m_Shader(parent) 
	{}

	void Update(const T &new_value)
	{
		m_Value = new_value;
	}

	void Submit() const
	{
		assert(false);
	}

private:
	T m_Value;
	Shader &m_Shader;
	unsigned m_Location;

	DISALLOW_COPY_AND_ASSIGN(Uniform);
};

UniformInterface* UniformCreate(unsigned type, int location, Shader &shader);

}  // namespace dry

#endif  // DRY_GRAPHICS_UNIFORM_H_