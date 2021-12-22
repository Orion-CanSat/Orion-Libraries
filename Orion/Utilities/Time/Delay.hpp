#ifndef __ORION_UTILITIES_TIME_DELAY_H__
#define __ORION_UTILITIES_TIME_DELAY_H__

#include "Orion/Orion.hpp"

#include <stdint.h>

namespace Orion
{
    namespace Utilities
    {
        namespace Time
        {
            class Delay
            {
                public:
                    /**
                    * This function will delay the specified amount of milliseconds.
                    * Do note that this function should not be paired with other classes
                    * from the Time namespace.
                    * 
                    * @param duration The milliseconds that the fuction will delay.
                    */
                    static void DelayMS(uint32_t duration);

                    /**
                    * This function will delay the specified amount of seconds.
                    * Do note that this function should not be paired with other classes
                    * from the Time namespace.
                    * 
                    * @param duration The milliseconds that the fuction will delay.
                    */
                    static void DelayS(uint32_t duration);
            };
        }
    }
}

#endif//__ORION_UTILITIES_TIME_DELAY_H__