//
//  Timer.h
//  dryGL
//
//  Created by Jordi Ros on 15/02/13.
//  Copyright (c) 2013 Jordi Ros. All rights reserved.
//

#pragma once

class Timer
{
public:

    Timer()
    {
        reset();
    }
    
    void reset()
    {
        m_TimeIni   = 0;
        m_TimePause = 0.f;
        m_Paused    = false;
    }
    
    void pause()
    {
      if (!m_Paused)
      {
        m_TimePause = getTime();
        m_Paused    = true;
      }
    }
    
    void resume()
    {
      if (m_Paused)
      {
        m_TimeIni+= getTime() - m_TimePause;
        m_Paused  = false;
      }
    }
    
    float getTime()
    {
      if (m_Paused)
      {
        return m_TimePause;
      }
      else
      {
        return m_TimeIni;
      }
    }

  protected:

    float   m_TimeIni;
    float   m_TimePause;
    bool    m_Paused;
};
