#ifndef __ORION_UTILITIES_TIME_TIME_H__
#define __ORION_UTILITIES_TIME_TIME_H__

#include "Orion/Orion.hpp"

#include <stdint.h>

namespace Orion
{
    namespace Utilities
    {
        namespace Time
        {
            class Time
            {
                public:
                    /**
                    * This function will return the milliseconds from boot.
                    * 
                    * @return Returns the current up time from boot in milliseconds
                    */
                    static uint32_t CurrentTimeMSFromBoot();
            };
        }
    }
}

#endif//__ORION_UTILITIES_TIME_TIME_H__