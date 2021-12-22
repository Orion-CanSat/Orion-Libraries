#include "Orion/Utilities/Time/Delay.hpp"

#if defined(ARDUINO)
    #include <Arduino.h>
#endif

using namespace Orion::Utilities::Time;

void Delay::DelayMS(uint32_t duration)
{
#if defined(ARDUINO)
    delay(duration);
#endif
}

void Delay::DelayS(uint32_t duration)
{
    Delay::DelayMS(1000 * duration);
}