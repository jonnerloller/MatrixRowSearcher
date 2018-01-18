#include "../include/timer.hpp"
namespace CP
{
    void Timer::StartTimer(void) noexcept
    {
        m_Start = now();
    }

    void Timer::StopTimer(void) noexcept
    {
        m_End = now();
    }

    double Timer::ToMilliseconds(const Nanoseconds ns) noexcept
    {
        return ns.count() * (1.0 / 1000000.0);
    }

    double Timer::ToMilliseconds(const Seconds s) noexcept
    {
        return s.count()  * (1000.0);
    }

    double Timer::ToSeconds(const Milliseconds ms) noexcept
    {
        return ms.count() * (1.0 / 1000.0);
    }

    double Timer::ToSeconds(const Nanoseconds ns) noexcept
    {
        return ns.count() * (1.0 / 1000000000.0);
    }

    Timer::Nanoseconds Timer::TripNanoseconds(void) noexcept
    {
        StopTimer();
        const Nanoseconds elapsedNanoseconds = GetNanoseconds();
        StartTimer();
        return elapsedNanoseconds;
    }

    Timer::Milliseconds Timer::TripMilliseconds(void) noexcept
    {
        StopTimer();
        const Milliseconds elapsedMilliseconds = GetMilliseconds();
        StartTimer();
        return elapsedMilliseconds;
    }

    Timer::Seconds Timer::TripSeconds(void) noexcept
    {
        StopTimer();
        const Seconds elapsedSeconds = GetSeconds();
        StartTimer();
        return elapsedSeconds;
    }

    Timer::Nanoseconds Timer::GetNanoseconds(void) const noexcept
    {
        const Nanoseconds elapsedNanoseconds = std::chrono::duration_cast<Nanoseconds>(m_End - m_Start);
        return elapsedNanoseconds;
    }

    Timer::Milliseconds Timer::GetMilliseconds(void) const noexcept
    {
        const Milliseconds elapsedMilliseconds = std::chrono::duration_cast<Milliseconds>(m_End - m_Start);
        return elapsedMilliseconds;
    }

    Timer::Seconds Timer::GetSeconds(void) const noexcept
    {
        const Seconds elapsedSeconds = std::chrono::duration_cast<Seconds>(m_End - m_Start);
        return elapsedSeconds;
    }
}