#include "Orion/Utilities/Time/Time.hpp"

#if defined(ARDUINO)
    #include <Arduino.h>
#endif

using namespace Orion::Utilities::Time;

uint32_t Time::CurrentTimeMSFromBoot()
{
    uint32_t currentTime;
#if defined(ARDUINO)
    currentTime = millis();
#endif

    return currentTime;
}