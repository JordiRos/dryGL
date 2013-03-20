//
//  Timer.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

namespace dry {
    
class Timer
{
public:

    Timer() { Reset(); }

    void Reset()
    {
        m_TimeIni   = 0;
        m_TimePause = 0.f;
        m_Paused    = false;
    }
    
    void Pause()
    {
        if (!m_Paused)
        {
            m_TimePause = GetTime();
            m_Paused    = true;
        }
    }
    
    void Resume()
    {
        if (m_Paused)
        {
            m_TimeIni+= GetTime() - m_TimePause;
            m_Paused  = false;
        }
    }
    
    float GetTime()
    {
        if (m_Paused)
            return m_TimePause;
        return dry::GetTime() - m_TimeIni;
    }

  protected:

    float   m_TimeIni;
    float   m_TimePause;
    bool    m_Paused;
};

}