#include "Orion/Utilities/Time/Timeout.hpp"

#include "Orion/Utilities/Time/Time.hpp"

using namespace Orion::Utilities::Time;

bool Timeout::WaitTimeout(bool(*func)(void*), void* ptr, uint32_t duration)
{
    bool last = false;
    uint32_t startTime = Time::CurrentTimeMSFromBoot();
    while (!last && startTime + duration > Time::CurrentTimeMSFromBoot())
        last = (*func)(ptr);
    return last;
}

bool Timeout::WaitTimeout(bool(*func)(), uint32_t duration)
{
    bool last = false;
    uint32_t startTime = Time::CurrentTimeMSFromBoot();
    while (!last && startTime + duration > Time::CurrentTimeMSFromBoot())
        last = (*func)();
    return last;
}

void Timeout::WaitTimeout(void(*func)(void*), void* ptr, uint32_t duration)
{
    uint32_t startTime = Time::CurrentTimeMSFromBoot();
    while (startTime + duration > Time::CurrentTimeMSFromBoot())
        (*func)(ptr);
}

void Timeout::WaitTimeout(void(*func)(), uint32_t duration)
{
    uint32_t startTime = Time::CurrentTimeMSFromBoot();
    while (startTime + duration > Time::CurrentTimeMSFromBoot())
        (*func)();
}

void* Timeout::WaitTimeout(void*(*func)(void*), void* ptr, uint32_t duration)
{
    void* last = nullptr;
    uint32_t startTime = Time::CurrentTimeMSFromBoot();
    while (!last && startTime + duration > Time::CurrentTimeMSFromBoot())
        last = (*func)(ptr);
    return last;
}

void* Timeout::WaitTimeout(void*(*func)(), uint32_t duration)
{
    void* last = nullptr;
    uint32_t startTime = Time::CurrentTimeMSFromBoot();
    while (!last && startTime + duration > Time::CurrentTimeMSFromBoot())
        last = (*func)();
    return last;
}