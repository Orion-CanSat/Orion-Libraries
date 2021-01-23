#ifndef __ORION_UTILITIES_INTERRUPTS_SOFTWAREINTERRUPTS_H__
#define __ORION_UTILITIES_INTERRUPTS_SOFTWAREINTERRUPTS_H__

#include <stdarg.h>

namespace Orion
{
    namespace Utilities
    {
        namespace Interrupts
        {
            class Interrupts
            {
                public:
                    static void EnableInterrupts();
                    static void DisableInterrupts();
                    static void AddInterrupt(int, void(*)(va_list));
                    static void Interrupt(int);
            };
        }
    }
}


#endif//__ORION_UTILITIES_INTERRUPTS_SOFTWAREINTERRUPTS_H__