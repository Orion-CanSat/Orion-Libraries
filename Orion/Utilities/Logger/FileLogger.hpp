#ifndef __ORION_UTILITIES_LOGGER_FILELOGGER_H__
#define __ORION_UTILITIES_LOGGER_FILELOGGER_H__

#include "Orion.h"

#include "Orion/Utilities/Memory/Buffer.hpp"

#ifdef ARDUINO
    #include <SD.h>
    #define FILE File
#else
    #include <stdio.h>
#endif

namespace Orion
{
    namespace Utilities
    {
        namespace Logger
        {
            class FileLogger : public Memory::Buffer
            {
                private:
                    const char* _fname;
                    FILE _fptr;

                public:
                    FileLogger(const char* fname, uint32_t size);

                    Memory::Buffer operator<<(const char* vl);
                    
                    void Flush();

                    ~FileLogger();
            };
        }
    }
}

#endif//__ORION_UTILITIES_LOGGER_FILELOGGER_H__