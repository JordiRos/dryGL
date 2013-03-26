//------------------------------------------------------------------------------
// Random.h
// This source is public domain
//------------------------------------------------------------------------------

#pragma once

namespace dry {

class Random
{
private:
    enum
    {
        N = 624,
        M = 397,
        HighBitMask = 0x80000000,
        LowBitsMask = 0x7FFFFFFF,
    };
    
public:
    Random() { Seed(); }
    
	void Seed()
	{
		uint init[2];
        init[0] = (uint)time(NULL);
        init[1] = (uint)time(NULL) + 1337;
		Seed(init, 2);
	}
    
	void Seed(uint p_SeedVal)
	{
		m_State[0] = p_SeedVal;
		for(uint ii = 1; ii < N; ++ii)
		{
			m_State[ii] = 0x6C078965 * (m_State[ii-1] ^ (m_State[ii-1] >> 30)) + ii;
		}
		m_Index = N;
	}
    
	void Seed(uint *p_Seed, uint p_SeedLen)
	{
		Seed(0x12BD6AA);
		uint Iter = (N > p_SeedLen) ? N : p_SeedLen;
		uint StateIdx = 1, SeedIdx = 0;
		for(; Iter > 0; --Iter)
		{
			m_State[StateIdx] = (m_State[StateIdx] ^
                                 ((m_State[StateIdx-1] ^ (m_State[StateIdx-1] >> 30)) * 0x19660D))
            + SeedIdx + p_Seed[SeedIdx];
			if(++StateIdx >= N)
			{
				m_State[0] = m_State[N-1];
				StateIdx = 1;
			}
			++SeedIdx;
			SeedIdx %= p_SeedLen;
		}
		for(Iter = N-1; Iter > 0; --Iter)
		{
			m_State[StateIdx] =(m_State[StateIdx] ^
                                ((m_State[StateIdx-1] ^ (m_State[StateIdx-1] >> 30)) * 0x5D588B65))
            - StateIdx;
			if(++StateIdx >= N)
			{
				m_State[0] = m_State[N-1];
				StateIdx = 1;
			}
		}
		m_State[0] = HighBitMask;
	}
    
	uint Next()
	{
		if (m_Index >= N)
			Update();
		uint Value = m_State[m_Index++];
		Value ^= (Value >> 11);
		Value ^= (Value << 7 ) & 0x9D2C5680;
		Value ^= (Value << 15) & 0xEFC60000;
		Value ^= (Value >> 18);
		return Value;
	}
    
	int Next(int max)
	{
		return (((uint(Next()) >> 16) * int(max+1)) >> 16);
	}
    
    int Next(int min, int max)
    {
        return Next(max-min) + min;
    }

    float Next(float max)
    {
        return (float)Next(1<<16) * max * (1.f / (float)(1<<16));
    }

    float Next(float min, float max)
    {
        return Next(max-min) + min;
    }

private:
    
	uint m_State[624];
	ushort m_Index;
    
	uint Twist(uint p_Mod, uint p_Base, uint p_Next)
	{
		const uint Magic[2] = {0x0, 0x9908B0DF};
		const uint Mixed = (p_Base & HighBitMask) | (p_Next & LowBitsMask);
		return p_Mod ^ Magic[Mixed & 0x1] ^ (Mixed >> 1);
	}
    
	void Update(void)
	{
		m_Index = 0;
		for(uint ii = 0; ii < (N-M); ++ii)
		{
			m_State[ii] = Twist(m_State[ii + M], m_State[ii], m_State[ii+1]);
		}
		for(uint ii = (N-M); ii < N-1; ++ii)
		{
			m_State[ii] = Twist(m_State[ii-N+M], m_State[ii], m_State[ii+1]);
		}
		m_State[N-1] = Twist(m_State[M-1], m_State[N-1], m_State[0]);
	}
    
};

}