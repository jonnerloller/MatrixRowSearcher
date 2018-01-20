#ifndef TIMER_HPP
#define TIMER_HPP
#include <chrono>
namespace CP
{
    class Timer : public std::chrono::high_resolution_clock
    {
    public:
        using Nanoseconds = std::chrono::nanoseconds;
        using Milliseconds = std::chrono::milliseconds;
        using Seconds = std::chrono::seconds;

        void            StartTimer(void) noexcept;
        void            StopTimer(void) noexcept;
        static double   ToMilliseconds(const Nanoseconds   ns) noexcept;
        static double   ToMilliseconds(const Seconds       s) noexcept;
        static double   ToSeconds(const Milliseconds  ms) noexcept;
        static double   ToSeconds(const Nanoseconds   ns) noexcept;
        Nanoseconds     SplitNanoseconds(void) noexcept;
        Milliseconds    SplitMilliseconds(void) noexcept;
        Seconds         SplitSeconds(void) noexcept;
        Nanoseconds     GetNanoseconds(void) const noexcept;
        Milliseconds    GetMilliseconds(void) const noexcept;
        Seconds         GetSeconds(void) const noexcept;

    protected:

        time_point        m_Start;
        time_point        m_End;
    };
}
#endif