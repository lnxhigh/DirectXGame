#pragma once

#include "Timer.h"
#include <windows.h>

Timer::Timer()
    : m_seconds_per_count(0.0), 
    m_delta_time(-1.0), m_base_time(0), m_paused_time(0),
    m_stop_time(0), m_prev_time(0), m_curr_time(0), 
    m_stopped(false) 
{
    __int64 frequency = 0;
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
    m_seconds_per_count = 1.0 / (double) frequency;

    Reset();
}

float Timer::TotalTime() const
{
    // Do not count the time that has passed since we stopped.
    __int64 recent_time = m_stopped ? m_stop_time : m_curr_time;
    __int64 counts = (recent_time - m_base_time) - m_paused_time;
    return (float)(counts * m_seconds_per_count);
}

float Timer::DeltaTime() const
{
    return (float) m_delta_time;
}

void Timer::Reset()
{
    __int64 curr_time = 0;
    QueryPerformanceCounter((LARGE_INTEGER*)&curr_time);
    m_base_time = curr_time;
    m_prev_time = curr_time;
    m_stop_time = 0;
    m_stopped = false;
}

// Accumulate the time elapsed between stop and start pairs.
void Timer::Start()
{
    if (!m_stopped)
    {
        return;
    }

    __int64 start_time = 0;
    QueryPerformanceCounter((LARGE_INTEGER*)&start_time);
    
    // Accumulate the paused time.
    m_paused_time += (start_time - m_stop_time);

    // Reset prvious time to the current time.
    m_prev_time = start_time;
    
    // No longer stopped
    m_stop_time = 0;
    m_stopped = false;
}

void Timer::Stop()
{
    if (m_stopped)
    {
        return;
    }

    __int64 curr_time = 0;
    QueryPerformanceCounter((LARGE_INTEGER*)&curr_time);
    
    // Save the time we stopped at 
    // Set the Boolean flag indicating the timer is stopped.
    m_stop_time = curr_time;
    m_stopped = true;
}

void Timer::Tick()
{
    if (m_stopped)
    {
        m_delta_time = 0.0;
        return;
    }

    // Get the time this frame.
    __int64 curr_time = 0;
    QueryPerformanceCounter((LARGE_INTEGER*)&curr_time);
    m_curr_time = curr_time;

    // Time difference between this frame and the previous.
    __int64 diff = m_curr_time - m_prev_time;
    m_delta_time = diff * m_seconds_per_count;
    
    // Prepare for next frame.
    m_prev_time = m_curr_time;

    // Force nonnegative
    if (m_delta_time < 0.0)
    {
        m_delta_time = 0.0;
    }
}

