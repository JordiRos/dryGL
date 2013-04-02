//
//  Uniform.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#ifndef DRY_GRAPHICS_UNIFORM_H_
#define DRY_GRAPHICS_UNIFORM_H_

namespace dry {

template<typename T> class UniformT;

class Uniform
{
public:
    static Uniform     *Create  (int location, int gltype);

public:
	virtual            ~Uniform () {}

	template<typename T>
    void                Update  (const T &value) { (static_cast<UniformT<T>*>(this))->Update(value); }
	virtual void        Bind    () = 0;
};

//------------------------------------------------------------------------------------------------
// Uniform data template
//------------------------------------------------------------------------------------------------
template<typename T>
class UniformT : public Uniform
{
public:
                        UniformT(unsigned location) : m_Location(location), m_Submit(false) {}

	void                Update  (const T &value) { m_Value = value; m_Submit = true; }
	void                Bind    () { assert(false); }

private:
	T                   m_Value;
    bool                m_Submit;
	unsigned            m_Location;

	DISALLOW_COPY_AND_ASSIGN(UniformT);
};

}

#endif
