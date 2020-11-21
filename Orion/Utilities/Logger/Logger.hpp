#ifndef __ORION_UTILITIES_LOGGER_LOGGER_H__
#define __ORION_UTILITIES_LOGGER_LOGGER_H__

#include "Orion.h"

#include "Orion/Utilities/Memory/Buffer.hpp"

namespace Orion
{
    namespace Utilities
    {
        namespace Logger
        {
            class Logger : public Memory::Buffer
            {
                public:
                    Logger() { }
            };
        }
    }
}

#endif//__ORION_UTILITIES_LOGGER_LOGGER_H__